#include "sysinfo.h"
// Linux 版本的系统信息获取
// 读取 /proc/cpuinfo 和 /proc/meminfo 文件以及使用 std::filesystem 获取磁盘信息
#if defined(__linux__)
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
SYSinfo::SYSinfo() {
    std::ifstream cpuinfo_file("/proc/cpuinfo");
    std::ifstream meminfo_file("/proc/meminfo");
    std::string line;
    std::string cpu_name = "";
    std::string cpu_cores = "";
    std::string cpu_threads = "";
    // 读取cpu信息
    while (std::getline(cpuinfo_file, line)) {
        if (line.find("model name") != std::string::npos) {
            cpu_name = line.substr(line.find(":"));
            continue;
        }
        if (line.find("cpu cores") != std::string::npos) {
            cpu_cores = line.substr(line.find(":"));
            continue;
        }
        if (line.find("siblings") != std::string::npos) {
            cpu_threads = line.substr(line.find(":"));
            continue;
        }
    }
    cpuinfo_file.close();
    // 读取内存信息
    while (std::getline(meminfo_file, line)) {
        if (line.find("MemTotal") != std::string::npos) {
            std::string mem_total = line.substr(line.find(":") + 1);
            mem_total = mem_total.substr(mem_total.find_first_not_of(' '));
            m_data[4] += ": " + mem_total;
            break;
        }
    }
    meminfo_file.close();
    m_data[1] += std::move(cpu_name);
    m_data[2] += std::move(cpu_cores);
    m_data[3] += std::move(cpu_threads);

    // 读取磁盘信息
    std::filesystem::space_info fs = std::filesystem::space("/");
    m_data[5] += ": " + std::to_string(fs.capacity / 1024 / 1024) + "MB";
}
#elif defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(__NT__)
// Windows 版本的系统信息获取，使用 Windows API
#include <windows.h>

#include <sstream>
#include <vector>

SYSinfo::SYSinfo() {
    // CPU name
    std::string cpuName;
    getCPUname(cpuName);
    m_data[1] += ": " + cpuName;

    // CPU cores
    int nCores = 0;
    getCPUInfo(nCores);
    m_data[2] += ": " + std::to_string(nCores);

    // CPU threads
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    m_data[3] += ": " + std::to_string(sysInfo.dwNumberOfProcessors);

    // Memory
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    GlobalMemoryStatusEx(&memStatus);
    std::ostringstream ss;
    ss << memStatus.ullTotalPhys / (1024 * 1024) << " MB";
    m_data[4] += ": " + ss.str();
    ss.str("");
    ss.clear();

    // Disk space
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes,
        totalNumberOfFreeBytes;
    ULARGE_INTEGER totalDiskSpace{0, 0};
    std::string drives = "C:\\";
    while (GetDiskFreeSpaceExA(drives.c_str(), &freeBytesAvailable,
                               &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        totalDiskSpace.QuadPart += totalNumberOfBytes.QuadPart;
        drives[0]++;
    }
    m_data[5] +=
        ": " + std::to_string(totalDiskSpace.QuadPart / (1024 * 1024 * 1024)) +
        " GB";
}

void SYSinfo::getCPUInfo(int& cpu_cores) {
    DWORD bufferSize = 0;
    GetLogicalProcessorInformation(nullptr, &bufferSize);
    std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));

    if (!GetLogicalProcessorInformation(buffer.data(), &bufferSize)) {
        return;
    }
    for (const auto& info : buffer) {
        if (info.Relationship == RelationProcessorCore) {
            cpu_cores++;
        }
    }
}

void SYSinfo::getCPUname(std::string& cpuName) {
    HKEY hKey;
    char cpuNameBuffer[256];
    DWORD bufferSize = sizeof(cpuNameBuffer);
    // 读取注册表
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                      "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
                      KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegQueryValueExA(hKey, "ProcessorNameString", NULL, NULL,
                         (LPBYTE)cpuNameBuffer, &bufferSize);
        RegCloseKey(hKey);
    }
    cpuName = cpuNameBuffer;
}
#endif
