#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <thread>
#include <nlohmann/json.hpp>

#ifdef __APPLE__
#include <mach/mach.h>
#include <sys/sysctl.h>
#include <unistd.h>
#elif __linux__
#include <sys/sysinfo.h>
#include <fstream>
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#include <psapi.h>
#endif

class MemoryUtil {
public:
    struct MemoryInfo {
        long totalMemory = 0;
        long freeMemory = 0;
        long usedMemory = 0;
        long maxMemory = 0;
        int availableProcessors = 0;
    };

    // 메모리 사용량을 바이트 단위로 포맷팅
    static std::string formatMemoryUsage(long memoryBytes) {
        double memoryMB = memoryBytes / (1024.0 * 1024.0);
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << memoryMB << " MB";
        return oss.str();
    }

    // 현재 프로세스의 메모리 정보 가져오기
    static MemoryInfo getCurrentProcessMemory() {
        MemoryInfo info;
        
#ifdef __APPLE__
        // macOS 구현
        mach_task_basic_info_data_t taskInfo;
        mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
        
        if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, 
                      (task_info_t)&taskInfo, &count) == KERN_SUCCESS) {
            info.usedMemory = taskInfo.resident_size;
        }
        
        // 시스템 전체 메모리
        int64_t totalMem;
        size_t size = sizeof(totalMem);
        sysctlbyname("hw.memsize", &totalMem, &size, NULL, 0);
        info.totalMemory = totalMem;
        
        // 사용 가능한 메모리 (근사치)
        vm_size_t page_size;
        vm_statistics64_data_t vm_stat;
        mach_msg_type_number_t host_count = sizeof(vm_stat) / sizeof(natural_t);
        
        if (host_page_size(mach_host_self(), &page_size) == KERN_SUCCESS &&
            host_statistics64(mach_host_self(), HOST_VM_INFO64, 
                            (host_info64_t)&vm_stat, &host_count) == KERN_SUCCESS) {
            info.freeMemory = (vm_stat.free_count + vm_stat.inactive_count) * page_size;
        }
        
        info.maxMemory = info.totalMemory; // macOS에서는 동일
        
#elif __linux__
        // Linux 구현
        struct sysinfo si;
        if (sysinfo(&si) == 0) {
            info.totalMemory = si.totalram * si.mem_unit;
            info.freeMemory = si.freeram * si.mem_unit;
            info.usedMemory = info.totalMemory - info.freeMemory;
            info.maxMemory = info.totalMemory;
        }
        
        // 프로세스별 메모리는 /proc/self/status에서 읽기
        std::ifstream statusFile("/proc/self/status");
        std::string line;
        while (std::getline(statusFile, line)) {
            if (line.find("VmRSS:") == 0) {
                std::istringstream iss(line);
                std::string label, value, unit;
                iss >> label >> value >> unit;
                info.usedMemory = std::stol(value) * 1024; // kB to bytes
                break;
            }
        }
        
#elif _WIN32
        // Windows 구현
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            info.usedMemory = pmc.WorkingSetSize;
        }
        
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        if (GlobalMemoryStatusEx(&memInfo)) {
            info.totalMemory = memInfo.ullTotalPhys;
            info.freeMemory = memInfo.ullAvailPhys;
            info.maxMemory = info.totalMemory;
        }
#endif

        // 사용 가능한 프로세서 수
        info.availableProcessors = std::thread::hardware_concurrency();
        
        return info;
    }

    // 현재 메모리 상태를 JSON으로 반환
    static nlohmann::json getCurrentMemoryJson() {
        MemoryInfo info = getCurrentProcessMemory();
        
        nlohmann::json response;
        response["totalMemory"] = formatMemoryUsage(info.totalMemory);
        response["freeMemory"] = formatMemoryUsage(info.freeMemory);
        response["usedMemory"] = formatMemoryUsage(info.usedMemory);
        response["maxMemory"] = formatMemoryUsage(info.maxMemory);
        
        // 메모리 사용률 계산
        double usagePercent = 0.0;
        if (info.totalMemory > 0) {
            usagePercent = (double)info.usedMemory / info.totalMemory * 100.0;
        }
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << usagePercent << "%";
        response["memoryUsagePercent"] = oss.str();
        
        return response;
    }

    // 메모리 통계를 JSON으로 반환
    static nlohmann::json getMemoryStatsJson() {
        MemoryInfo info = getCurrentProcessMemory();
        
        nlohmann::json response;
        response["availableProcessors"] = info.availableProcessors;
        response["totalMemory"] = formatMemoryUsage(info.totalMemory);
        response["freeMemory"] = formatMemoryUsage(info.freeMemory);
        response["maxMemory"] = formatMemoryUsage(info.maxMemory);
        response["usedMemory"] = formatMemoryUsage(info.usedMemory);
        
        return response;
    }
};