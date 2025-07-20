package com.benchmark.benchmark.controller.algorithm;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import com.benchmark.benchmark.util.BenchmarkUtil;
import java.util.HashMap;
import java.util.Map;

@RestController
public class PrimeNumberController {

    @PostMapping("/prime-number")
    public Map<String, Object> calculatePrimeNumber(@RequestBody Map<String, Long> request) {
        long number = request.get("number");
        
        // 입력값 검증
        Map<String, Object> validationError = BenchmarkUtil.validateInput(number);
        if (validationError != null) {
            return validationError;
        }
        
        // 시간 측정 시작
        long startTime = BenchmarkUtil.getStartTime();
        
        // 알고리즘 실행
        boolean isPrime = primeNumber(number);
        
        // 시간 측정 종료
        long endTime = BenchmarkUtil.getEndTime();
        
        // 결과 생성
        Map<String, Object> response = new HashMap<>();
        response.put("isPrime", isPrime);
        response.put("executionTime", BenchmarkUtil.formatExecutionTime(startTime, endTime));
        response.put("executionTimeNanos", endTime - startTime);
        
        return response;
    }
    
    private boolean primeNumber(long number) {
        if (number <= 1) return false;
        
        boolean[] isPrime = new boolean[(int) (number + 1)];
        for (int i = 2; i <= number; i++) {
            isPrime[i] = true;
        }
        
        for (int p = 2; p * p <= number; p++) {
            if (isPrime[p]) {
                for (int i = p * p; i <= number; i += p) {
                    isPrime[i] = false;
                }
            }
        }
        
        return isPrime[(int) number];
    }
}
