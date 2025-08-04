//
// Created by sword on 7/29/2025.
//
#include "VROMFs.h"

void VromfsFile::Save(std::ofstream *cb)
{
    auto blk = owner->parseFileToDatablock(*this);
    if(blk)
    {
        std::ostringstream ss;

        //blk->saveText(&ss, 0);
        auto s = ss.str();
        //cb->write(s.c_str(), s.size());
    }
    else
    {
        auto raw = this->readRaw();
        //cb->write(raw.data(), raw.size());
    }
}

