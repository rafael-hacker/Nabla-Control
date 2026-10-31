#include <vector>
#include <string>

struct CpuUsage{
    double cpu;
    std::vector<double> cpus;
};

struct CpuTimes{
    std::string names;
    long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
};

std::vector<CpuTimes> CpuRead();
CpuUsage CpuUsageCalculate();
