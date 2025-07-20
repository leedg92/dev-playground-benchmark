package com.benchmark.benchmark.controller.algorithm;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import com.benchmark.benchmark.util.BenchmarkUtil;
import java.util.HashMap;
import java.util.Map;

@RestController
public class FibonacciController {

    @PostMapping("/fibonacci")
    public Map<String, Object> calculateFibonacci(@RequestBody Map<String, Long> request) {
        long number = request.get("number");
        
        // 입력값 검증
        Map<String, Object> validationError = BenchmarkUtil.validateInput(number);
        if (validationError != null) {
            return validationError;
        }
        
        // 시간 측정 시작
        long startTime = BenchmarkUtil.getStartTime();
        
        // 알고리즘 실행
        long result = fibonacci(number);
        
        // 시간 측정 종료
        long endTime = BenchmarkUtil.getEndTime();
        
        // 결과 생성
        Map<String, Object> response = new HashMap<>();
        response.put("result", result);
        response.put("executionTime", BenchmarkUtil.formatExecutionTime(startTime, endTime));
        response.put("executionTimeNanos", endTime - startTime);
        
        return response;
    }

    private long fibonacci(long n) {
        if (n <= 1) return n;
        long a = 0, b = 1, c;
        for (long i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
}
