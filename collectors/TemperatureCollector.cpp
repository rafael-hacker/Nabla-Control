#include "../include/Temperature.hpp"
#include <exception>
#include <fstream>
#include <string>
#include <iostream>

double GetTemp(){
    double temperature{};
    std::string file_path = "/sys/class/thermal/thermal_zone0/temp";
    std::ifstream tempfile(file_path);
    std::string line;
    std::getline(tempfile, line);
    tempfile.close();

    try {
        temperature = std::stoi(line) / 1000.0;
    } catch (const std::exception& e){
        std::cerr << "[ERROR] " << e.what();
    }

    return temperature;
}
