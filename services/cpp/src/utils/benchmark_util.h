#pragma once

#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

class BenchmarkUtil {
public:
    // C++20 auto 매개변수 사용
    static auto getStartTime() {
        return std::chrono::high_resolution_clock::now();
    }
    
    static auto getEndTime() {
        return std::chrono::high_resolution_clock::now();
    }
    
    // auto 매개변수로 깔끔하게!
    static long getExecutionTimeNanos(auto startTime, auto endTime) {
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        return duration.count();
    }
    
    // 실행 시간을 초 단위로 포맷팅
    static std::string formatExecutionTime(auto startTime, auto endTime) {
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        double seconds = duration.count() / 1'000'000'000.0;
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(3) << seconds << "s";
        return oss.str();
    }
    
    // 메모리 사용량을 메가바이트 단위로 포맷팅
    static std::string formatMemoryUsage(long memoryBytes) {
        double memoryMB = memoryBytes / (1024.0 * 1024.0);
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << memoryMB << " MB";
        return oss.str();
    }
    
    // 입력값 검증 유틸리티 메서드
    static nlohmann::json validateInput(long number, long maxValue, const std::string& errorMessage) {
        if (number >= maxValue) {
            nlohmann::json errorResponse;
            errorResponse["error"] = errorMessage;
            errorResponse["maxSupported"] = maxValue;
            return errorResponse;
        }
        return nlohmann::json(); // null 반환
    }
    
    // 검증 메서드
    static nlohmann::json validateInput(long number) {
        return validateInput(number, 10000000000L, "너무 큰 값이 입력됨. 100억 미만까지 지원합니다.");
    }
};