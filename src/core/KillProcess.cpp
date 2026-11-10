#include <sys/types.h>
#include <signal.h>
#include "../../include/KillProcess.hpp"

void kill_process(pid_t pid){
    kill(pid, SIGKILL);    
}

