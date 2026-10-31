#include <bits/c++config.h>
#include <fstream>
#include <string>
#include "../include/CPUCollector.hpp"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

// user nice system idle iowait irq softirq steal guest guest_nice.
double calc_percent(CpuTimes a, CpuTimes b){
    long long total_a = a.user + a.nice + a.system + a.idle + a.iowait + a.irq + a.softirq + a.steal + a.guest + a.guest_nice;
    long long total_b = b.user + b.nice + b.system + b.idle + b.iowait + b.irq + b.softirq + b.steal + b.guest + b.guest_nice;
    
    double idle_a = a.idle + a.iowait;
    double idle_b = b.idle + b.iowait;

    double total = total_b - total_a;
    double idle = idle_b - idle_a;
    double usage;
    return usage = 100 * (total - idle) / total;
}

std::vector <CpuTimes> CpuRead(){
    CpuTimes cpu_t{};
    std::vector<CpuTimes> cpus;
    
    std::ifstream cpu_path("/proc/stat");
    if (!cpu_path.is_open()){
        std::cerr << "Failed open /proc/stat";
        exit(1);
    }
    std::string line;
    while(std::getline(cpu_path, line)){
        if(!line.starts_with("cpu")){
            break;
        }
        std::istringstream ss(line);
        ss>>cpu_t.names>>cpu_t.user>>cpu_t.nice>>cpu_t.system>>cpu_t.idle>>cpu_t.iowait>>cpu_t.irq>>cpu_t.softirq>>cpu_t.steal>>cpu_t.guest>>cpu_t.guest_nice;
        cpus.push_back(cpu_t);       
    }
    return cpus;
}

CpuUsage CpuUsageCalculate(){
    CpuUsage cpus;
    std::vector <CpuTimes> after = CpuRead();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::vector<CpuTimes> before = CpuRead();
    if(after.empty() && after.size() != before.size()){
        return cpus;    
    }
    cpus.cpu = calc_percent(after[0], before[0]);
    for(size_t i=1; i < before.size(); i++){
       cpus.cpus.push_back(calc_percent(after[i], before[i])); 
    }
    after = before;
    return cpus;
}
