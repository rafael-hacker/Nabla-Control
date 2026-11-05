#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/NetworkCollector.hpp"
#include <chrono>
#include <thread>

NetCounter GetNetworkCounter(){
    NetCounter total{};

    std::string network_file = "/proc/net/dev";
    std::ifstream file(network_file);

    if (!file.is_open()){
        std::cerr << "[ERROR] failed to open " <<  network_file << '\n';
        exit(1); 
    }
    
    std::string line;
    std::getline(file, line);
    std::getline(file, line);


    while (std::getline(file, line)){
        unsigned long long rx_b{};
        unsigned long long tx_b{};   

        std::istringstream iss(line);
        std::string name;     
    
        iss >> std::ws;
        std::getline(iss, name, ':');

        if (name == "lo"){continue;}  

        unsigned long long skip;
        
        iss >> rx_b;
        for (size_t i=0; i < 7; i++){ iss >> skip;}
        iss >> tx_b;
        
        total.rx += rx_b;
        total.tx += tx_b;
    }
    
    return total;
 
}

NetworkStats GetNetworkStats(){
    NetworkStats stats;
    NetCounter before = GetNetworkCounter();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    NetCounter after = GetNetworkCounter();
    
    stats.rx_mbps = (after.rx - before.rx) / 1.0 / MB;
    stats.tx_mbps = (after.tx - before.tx) / 1.0 / MB;
    return stats;
}
