#pragma once
#include <string>

struct Temperature{
    double temperature_celsius;
    std::string type;
};

Temperature GetTemp();
