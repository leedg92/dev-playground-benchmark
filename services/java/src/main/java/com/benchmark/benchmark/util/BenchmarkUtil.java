package com.benchmark.benchmark.util;

import java.util.HashMap;
import java.util.Map;

public class BenchmarkUtil {
    
    /**
     * 시작 시간을 나노초 단위로 반환
     */
    public static long getStartTime() {
        return System.nanoTime();
    }
    
    /**
     * 종료 시간을 나노초 단위로 반환
     */
    public static long getEndTime() {
        return System.nanoTime();
    }

    
    /**
     * 실행 시간을 초 단위로 포맷팅
     */
    public static String formatExecutionTime(long startTime, long endTime) {
        long executionTimeNanos = endTime - startTime;
        double executionTimeSeconds = executionTimeNanos / 1_000_000_000.0;
        return String.format("%.3f", executionTimeSeconds) + "s";
    }
    
    /**
     * 메모리 사용량을 메가바이트 단위로 포맷팅
     */
    public static String formatMemoryUsage(long memoryBytes) {
        double memoryMB = memoryBytes / (1024.0 * 1024.0);
        return String.format("%.2f", memoryMB) + " MB";
    }
    
    /**
     * 입력값 검증 유틸리티 메서드
     * 
     * @param number 검증할 숫자
     * @param maxValue 최대 허용값
     * @param errorMessage 에러 메시지
     * @return 검증 실패시 에러 응답, 성공시 null
     */
    public static Map<String, Object> validateInput(long number, long maxValue, String errorMessage) {
        if (number >= maxValue) {
            Map<String, Object> errorResponse = new HashMap<>();
            errorResponse.put("error", errorMessage);
            errorResponse.put("maxSupported", maxValue);
            return errorResponse;
        }
        return null;
    }
    
    /**
     * 검증 메서드
     * 
     * @param number 검증할 숫자
     * @return 검증 실패시 에러 응답, 성공시 null
     */
    public static Map<String, Object> validateInput(long number) {
        return validateInput(number, 10000000000L, "너무 큰 값이 입력됨. 100억 미만까지 지원합니다.");
    }
} 