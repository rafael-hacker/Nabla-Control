#pragma once 
#include <vector>
#include "../../include/ProcessCollector.hpp"
#include "../../include/CPUCollector.hpp"
#include "../../include/DiskCollector.hpp"
#include "../../include/MemoryCollector.hpp"
#include "../../include/NetworkCollector.hpp"
#include "../../include/Temperature.hpp"

struct Systemsnapshot{
    CpuUsage cpu;
    DiskSpace disk;
    Memory memory;
    NetworkStats network;
    std::vector <ProcessInfo> processes;
    std::vector <Temperature> temperature;
};
