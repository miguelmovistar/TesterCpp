#include <iostream>
#include <pugixml.hpp>
#include <filesystem>
#include <unordered_map>
#include <functional>
#include "FileWatcher.h"

#include <thread>     // Para std::this_thread::sleep_for
#include <chrono>     // Para std::chrono

using namespace std;
using namespace pugi;

FileWatcher fileWatcher("C:\\CLEARX\\Config");

xml_document configurationFile1;

int main()
{
    fileWatcher.Inicia();
}

void GetConfigFile(FileWatcher fileWatcher)
{
    if (!fileWatcher._paths.empty()) 
    {
        configurationFile1.load_file(fileWatcher._paths.begin()->first.data());
    }
}




