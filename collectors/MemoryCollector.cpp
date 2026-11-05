#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/MemoryCollector.hpp"

Memory GetMemory(){
    Memory mem{};
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()){
        std::cerr << "[ERROR] Failed to open /proc/meminfo";
        exit(1);
    }

    std::string line;    
    unsigned long long mem_free;
    unsigned long long mem_avaliable;
    unsigned long long mem_total;

    while (std::getline(file, line)){
        if (line.starts_with("MemTotal:")){
            std::istringstream iss(line);
            std::string key;
            iss >> key >> mem_total;
        }
        if (line.starts_with("MemFree:")){
            std::istringstream iss(line);
            std::string key;
            iss >> key >> mem_free;
        }
        if (line.starts_with("MemAvailable:")){
            std::istringstream iss(line);
            std::string key;
            iss >> key >> mem_avaliable;
        }
    } 
    file.close();
    mem.memory_AvaliableGB = mem_avaliable / GB;
    mem.memory_freeGB = mem_free / GB;
    mem.memory_totalGB = mem_total / GB;

    mem.usage_percent = (mem.memory_totalGB - mem.memory_AvaliableGB / mem.memory_totalGB) / mem.memory_totalGB * 100;
    return mem;
}

