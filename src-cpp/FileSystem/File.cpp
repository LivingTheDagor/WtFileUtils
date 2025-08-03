//
// Created by sword on 7/12/2025.
//
#include "FileSystem.h"

std::span<char> HostFile::readRaw()
{
    std::ifstream inputFile(this->os_path, std::ios::binary);
    if(inputFile.is_open())
    {
        auto last_write = fs::last_write_time(this->os_path);
        if(last_write != last_write_time)
        {
            buffer = std::vector<char>(std::istreambuf_iterator<char>(inputFile), {});
            last_write_time = last_write;
        }
        return {buffer};
    }
    return {(char *)nullptr, 0};
}

void HostFile::Save(std::ofstream *cb)
{
    auto temp = readRaw();
    cb->write(temp.data(), temp.size());
}