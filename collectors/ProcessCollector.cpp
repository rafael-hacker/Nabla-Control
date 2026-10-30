// first version 
#include <algorithm>
#include <charconv>
#include <exception>
#include <filesystem>
#include <sys/types.h>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>

typedef struct {
    pid_t pid;
    std::string name;
}ProcessInfo;

const std::string pid_path = "/proc";

std::vector<ProcessInfo> ReadProcess(){    
    
    ProcessInfo process;
    std::vector<ProcessInfo> processes;
    try{
        for(const auto& entry: std::filesystem::directory_iterator(pid_path)){
                auto paths = entry.path().filename().string();
            try{
                if (std::all_of(paths.begin(), paths.end(), [](unsigned char c){return std::isdigit(c);})){
                    auto result = std::from_chars(paths.data(), (paths.data() + paths.size()), process.pid);
                    
                    if (result.ec != std::errc() || result.ptr != (paths.data() + paths.size()) ){
                        continue;
                    }

                    std::filesystem::path full_path = std::filesystem::path(pid_path) / std::filesystem::path(paths) / "comm";
                    std::ifstream file(full_path);
                    
                    if (!file.is_open()){
                        continue;
                    }

                    std::string filename;
                    if (!std::getline(file, filename) || filename.empty()){
                        continue;
                    }

                    process.name = filename;
                    processes.push_back(process);

                } else {
                    continue;
                }
            } catch (const std::exception& e){
                std::cerr << "[FAILED] " << e.what() << '\n';
            }
        }
    } catch (const std::filesystem::filesystem_error& e){
        std::cerr <<"[ERROR] " << e.what() << '\n';
    }

    return processes;
}
