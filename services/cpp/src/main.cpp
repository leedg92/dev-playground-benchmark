#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include "algorithms/fibonacci.h"
#include "algorithms/factorial.h"
#include "algorithms/prime_number.h"
#include "utils/benchmark_util.h"
#include "memory/memory.h"

int main() {
    httplib::Server svr;

    // 기본 경로 - 서버 상태 확인
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("C++ httplib API Server is running!", "text/plain");
    });

    // 피보나치 수열 API
    svr.Post("/fibonacci", [](const httplib::Request& req, httplib::Response& res) {
        try {
            auto json = nlohmann::json::parse(req.body);
            
            if (json.is_null()) {
                res.status = 400;
                res.set_content("Invalid JSON", "text/plain");
                return;
            }
            
            if (!json.contains("number")) {
                res.status = 400;
                res.set_content("Missing 'number' field", "text/plain");
                return;
            }
            
            long number = json["number"].get<long>();
            
            // 입력값 검증
            auto validationError = BenchmarkUtil::validateInput(number);
            if (!validationError.is_null()) {
                res.status = 400;
                res.set_content(validationError.dump(), "application/json");
                return;
            }
            
            // 시간 측정 시작
            auto startTime = BenchmarkUtil::getStartTime();
            
            // 알고리즘 실행
            long result = Fibonacci::calculate(number);
            
            // 시간 측정 종료
            auto endTime = BenchmarkUtil::getEndTime();
            
            // 결과 생성
            nlohmann::json response;
            response["result"] = result;
            response["executionTime"] = BenchmarkUtil::formatExecutionTime(startTime, endTime);
            response["executionTimeNanos"] = BenchmarkUtil::getExecutionTimeNanos(startTime, endTime);
            
            res.status = 200;
            res.set_content(response.dump(), "application/json");
            return;
            
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }
    });

    // 팩토리얼 API
    svr.Post("/factorial", [](const httplib::Request& req, httplib::Response& res) {
        try {
            auto json = nlohmann::json::parse(req.body);
            
            if (json.is_null()) {
                res.status = 400;
                res.set_content("Invalid JSON", "text/plain");
                return;
            }
            
            if (!json.contains("number")) {
                res.status = 400;
                res.set_content("Missing 'number' field", "text/plain");
                return;
            }
            
            long number = json["number"].get<long>();
            
            // 입력값 검증
            auto validationError = BenchmarkUtil::validateInput(number);
            if (!validationError.is_null()) {
                res.status = 400;
                res.set_content(validationError.dump(), "application/json");
                return;
            }
            
            // 시간 측정 시작
            auto startTime = BenchmarkUtil::getStartTime();
            
            // 알고리즘 실행
            long result = Factorial::calculate(number);
            
            // 시간 측정 종료
            auto endTime = BenchmarkUtil::getEndTime();
            
            // 결과 생성
            nlohmann::json response;
            response["result"] = result;
            response["executionTime"] = BenchmarkUtil::formatExecutionTime(startTime, endTime);
            response["executionTimeNanos"] = BenchmarkUtil::getExecutionTimeNanos(startTime, endTime);
            
            res.status = 200;
            res.set_content(response.dump(), "application/json");
            return;
            
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }
    });

    // 소수 찾기 API
    svr.Post("/prime-number", [](const httplib::Request& req, httplib::Response& res) {
        try {
            auto json = nlohmann::json::parse(req.body);
            
            if (json.is_null()) {
                res.status = 400;
                res.set_content("Invalid JSON", "text/plain");
                return;
            }
            
            if (!json.contains("number")) {
                res.status = 400;
                res.set_content("Missing 'number' field", "text/plain");
                return;
            }
            
            long number = json["number"].get<long>();
            
            // 입력값 검증
            auto validationError = BenchmarkUtil::validateInput(number);
            if (!validationError.is_null()) {
                res.status = 400;
                res.set_content(validationError.dump(), "application/json");
                return;
            }
            
            // 시간 측정 시작
            auto startTime = BenchmarkUtil::getStartTime();
            
            // 알고리즘 실행
            bool isPrime = PrimeNumber::isPrime(number);
            
            // 시간 측정 종료
            auto endTime = BenchmarkUtil::getEndTime();
            
            // 결과 생성
            nlohmann::json response;
            response["isPrime"] = isPrime;
            response["executionTime"] = BenchmarkUtil::formatExecutionTime(startTime, endTime);
            response["executionTimeNanos"] = BenchmarkUtil::getExecutionTimeNanos(startTime, endTime);
            
            res.status = 200;
            res.set_content(response.dump(), "application/json");
            return;
            
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }
    });

    // 헬스체크 엔드포인트
    svr.Get("/health", [](const httplib::Request& req, httplib::Response& res) {
        nlohmann::json response;
        response["status"] = "healthy";
        response["service"] = "cpp-httplib-api";
        res.status = 200;
        res.set_content(response.dump(), "application/json");
        return;
    });

    // 현재 메모리 상태 API
    svr.Get("/memory/current", [](const httplib::Request& req, httplib::Response& res) {
        try {
            nlohmann::json response = MemoryUtil::getCurrentMemoryJson();
            res.status = 200;
            res.set_content(response.dump(), "application/json");
            return;
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }
    });

    // 메모리 통계 API
    svr.Get("/memory/stats", [](const httplib::Request& req, httplib::Response& res) {
        try {
            nlohmann::json response = MemoryUtil::getMemoryStatsJson();
            res.status = 200;
            res.set_content(response.dump(), "application/json");
            return;
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content("Internal server error", "text/plain");
            return;
        }
    });

    // 타입 크기 확인 API (디버그용)
    svr.Get("/debug/types", [](const httplib::Request& req, httplib::Response& res) {
        nlohmann::json response;
        response["long_size"] = sizeof(long);
        response["long_long_size"] = sizeof(long long);
        response["unsigned_long_long_size"] = sizeof(unsigned long long);
        response["long_max"] = LONG_MAX;
        response["long_min"] = LONG_MIN;
        
        res.status = 200;
        res.set_content(response.dump(), "application/json");
        return;
    });

    // 서버 설정
    svr.listen("0.0.0.0", 8080);

    return 0;
}