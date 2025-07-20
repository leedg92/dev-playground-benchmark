#pragma once

#include <vector>
#include <cmath>

class PrimeNumber {
public:
    // 에라토스테네스의 체를 사용한 최적화된 소수 판별
    static bool isPrime(long number) {
        if (number <= 1) return false;
        if (number <= 3) return true;
        if (number % 2 == 0 || number % 3 == 0) return false;
        
        // 6k±1 형태의 수만 검사 (최적화)
        for (long i = 5; i * i <= number; i += 6) {
            if (number % i == 0 || number % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
    
    // 에라토스테네스의 체를 사용한 소수 목록 생성
    static std::vector<bool> generateSieve(long maxNumber) {
        std::vector<bool> isPrime(maxNumber + 1, true);
        isPrime[0] = isPrime[1] = false;
        
        for (long p = 2; p * p <= maxNumber; p++) {
            if (isPrime[p]) {
                for (long i = p * p; i <= maxNumber; i += p) {
                    isPrime[i] = false;
                }
            }
        }
        
        return isPrime;
    }
    
    // 특정 범위 내의 소수 개수 계산
    static long countPrimes(long maxNumber) {
        if (maxNumber < 2) return 0;
        
        auto sieve = generateSieve(maxNumber);
        long count = 0;
        
        for (long i = 2; i <= maxNumber; i++) {
            if (sieve[i]) count++;
        }
        
        return count;
    }
    
    // 밀러-라빈 소수 판별법 (큰 수에 대해서는 이 방법 사용)
    static bool isPrimeMillerRabin(long number) {
        if (number <= 1) return false;
        if (number <= 3) return true;
        if (number % 2 == 0) return false;
        
        // number - 1 = 2^r * d 형태로 분해
        long d = number - 1;
        long r = 0;
        while (d % 2 == 0) {
            d /= 2;
            r++;
        }
        
        // 작은 소수들로 테스트 (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37)
        std::vector<long> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        
        for (long base : bases) {
            if (base >= number) break;
            
            if (!millerRabinTest(number, d, r, base)) {
                return false;
            }
        }
        
        return true;
    }
    
private:
    // 밀러-라빈 테스트 헬퍼 함수
    static bool millerRabinTest(long number, long d, long r, long base) {
        long x = modPow(base, d, number);
        
        if (x == 1 || x == number - 1) return true;
        
        for (long i = 1; i < r; i++) {
            x = (x * x) % number;
            if (x == number - 1) return true;
            if (x == 1) return false;
        }
        
        return false;
    }
    
    // 모듈로 거듭제곱 계산
    static long modPow(long base, long exponent, long modulus) {
        long result = 1;
        base %= modulus;
        
        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = (result * base) % modulus;
            }
            base = (base * base) % modulus;
            exponent /= 2;
        }
        
        return result;
    }
};