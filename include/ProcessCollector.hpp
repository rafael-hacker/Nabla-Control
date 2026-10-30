#include <string>
#include <vector>

typedef struct {
    pid_t pid;
    std::string name;
}ProcessInfo;

const std::string pid_path = "/proc";

std::vector<ProcessInfo> ReadProcess();
