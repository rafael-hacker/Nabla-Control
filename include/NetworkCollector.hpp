#pragma  once

constexpr double MB = 1000.0 * 1000.0;

struct NetworkStats {
    double rx_mbps{}; // receiving 
    double tx_mbps{}; // sending
};

NetworkStats GetNetworkStats();
