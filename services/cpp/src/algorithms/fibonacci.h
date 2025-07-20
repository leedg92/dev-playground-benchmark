#pragma once

class Fibonacci {
public:
    // unsigned long long 사용 (더 큰 범위)
    static unsigned long long calculate(long n) {
        if (n <= 1) return n;
        
        unsigned long long a = 0, b = 1, c;
        for (long i = 2; i <= n; i++) {
            c = a + b;  // 오버플로우 발생해도 계속 진행
            a = b;
            b = c;
        }
        return b;
    }
};