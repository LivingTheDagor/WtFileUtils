//
// Created by sword on 7/12/2025.
//
#include <iostream>
#include "FileSystem.h"
#include "VROMFs.h"

int main()
{
    fs::path path(R"(C:\Users\samue\PycharmProjects\testPythonh\cpp\testFiles\top7500Clans)");
    path = path.relative_path();
    std::cout << path.relative_path().parent_path() << "\n";

    std::cout << *(path.begin()++) << "\n";
    int i = 0;
    for (auto it = path.begin(); it != path.end(); ++it, ++i)
    {
        std::cout << *it << "\n";
        std::cout << i;
        std::cout << ((bool)it->has_extension()) << "\n";

    }

    /*
    Directory x = Directory(std::string("cpp"));
    //x.loadFromOsPath(R"(C:\Users\samue\PycharmProjects\testPythonh\cpp)");
    x.loadFromOsPath(R"(C:\Users\samue\PycharmProjects\testPythonh\cpp)");
    auto f = x["FileSystem"]["CMakeLists.txt"];
    auto file = f.asFile();

    auto raw = file->readRaw();
    for (auto ch : raw)
        std::cout << ch;
    std::cout << "\n";

     */
    //x.print(0);
    //auto x2 = std::make_shared<DummyFile>(std::string("Hello1.womp"));

    //x.addFSObject(x2);
    //x.print(0);

    //auto test = x["Hello2.womp"];
    //std::cout << test->getName() << "\n";
}