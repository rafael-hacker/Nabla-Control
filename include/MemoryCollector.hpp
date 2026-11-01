struct Memory{
    double memory_freeGB;
    double memory_AvaliableGB;
    double memory_totalGB;
    
    double usage_percent;
};

constexpr double GB = 1024.0 * 1024.0 * 1024.0;

Memory GetMemory();
