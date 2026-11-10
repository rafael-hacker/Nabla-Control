#include <filesystem>
#include "../include/DiskCollector.hpp"

DiskSpace GetDiskSpace(){
    DiskSpace disk{};
    std::filesystem::space_info si = std::filesystem::space("/");
    
    disk.total = si.capacity / gb;
    disk.avaliable = si.available / gb;
    disk.free = si.free / gb;

    double used = disk.total - disk.free;

    disk.percent_usage = used / (used + disk.avaliable) * 100;

    disk.percent_available = disk.avaliable / disk.total * 100.0;

    return disk;
}
