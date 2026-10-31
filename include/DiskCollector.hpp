struct DiskSpace{
    double avaliable;
    double total;
 
    double free;

    double percent_usage;
    double percent_available;
};

constexpr double gb = 1024 * 1024 * 1024;

DiskSpace GetDiskSpace();
