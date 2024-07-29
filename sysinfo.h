#ifndef SYSINFO_H
#define SYSINFO_H
#include <array>
#include <string>

struct SYSinfo {
    std::array<std::string, 7> m_data = {
        "// SYSTEM SELF-TEST", "CPU_NAME", "CPU_CORES",
        "CPU_THREADS",         "MEMORY",    "DISK",     "// COMPLETE."};

    SYSinfo();
    void getCPUCore(int& cpu_cores);
    void getCPUname(std::string& cpuName);
};
#endif  // SYSINFO_H
