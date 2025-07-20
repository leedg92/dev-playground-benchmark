#pragma once

#include <vector>

class Factorial {
public:
    // 반복문을 사용한 최적화된 팩토리얼 계산
    static long calculate(long n) {
        if (n < 0) return -1;
        if (n == 0 || n == 1) return 1;
        if (n > 20) return -1; // long 타입 오버플로우 방지
        
        long result = 1;
        for (long i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
    
    // 재귀를 사용한 팩토리얼 계산 (작은 수에 대해서만)
    static long calculateRecursive(long n) {
        if (n < 0) return -1;
        if (n == 0 || n == 1) return 1;
        if (n > 20) return -1; // long 타입 오버플로우 방지
        
        return n * calculateRecursive(n - 1);
    }
    
    // 메모이제이션을 사용한 팩토리얼 계산
    static long calculateWithMemoization(long n) {
        if (n < 0) return -1;
        if (n == 0 || n == 1) return 1;
        if (n > 20) return -1; // long 타입 오버플로우 방지
        
        std::vector<long> memo(n + 1, -1);
        memo[0] = 1;
        memo[1] = 1;
        
        return factorialMemo(n, memo);
    }
    
private:
    // 메모이제이션 헬퍼 함수
    static long factorialMemo(long n, std::vector<long>& memo) {
        if (memo[n] != -1) return memo[n];
        
        memo[n] = n * factorialMemo(n - 1, memo);
        return memo[n];
    }
};