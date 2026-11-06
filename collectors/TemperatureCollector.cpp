#include "../include/Temperature.hpp"
#include <exception>
#include <fstream>
#include <string>
#include <iostream>

Temperature GetTemp(){
    Temperature temp;
    std::string file_path = "/sys/class/thermal/thermal_zone0/temp";
    std::ifstream tempfile(file_path);
    if (!tempfile.is_open()){
        std::cerr << "failed to open " << file_path << '\n';
        tempfile.close();
        exit(1);
    }

    std::string line;
    std::getline(tempfile, line);
    std::string filename_path = "/sys/class/thermal/thermal_zone0/type";
    
    std::ifstream filename(filename_path);

    if (!filename.is_open()){
        std::cerr << "failed to open " << filename_path  << '\n';
        filename.close();
        exit(1);
    }
    
    std::string name;
    std::getline(filename, name);

    temp.type = name;
    tempfile.close();
    filename.close();

    try {
        temp.temperature_celsius = std::stoi(line) / 1000.0;
    } catch (const std::exception& e){
        std::cerr << "[ERROR] " << e.what();
    }

    return temp;
}
