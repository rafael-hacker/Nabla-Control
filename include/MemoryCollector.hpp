#pragma once
struct Memory{
    double memory_freeGB;
    double memory_AvaliableGB;
    double memory_totalGB;
    
    double usage_percent;
};

constexpr double GB = 1024 * 1024;

Memory GetMemory();
