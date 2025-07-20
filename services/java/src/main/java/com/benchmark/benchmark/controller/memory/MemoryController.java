package com.benchmark.benchmark.controller.memory;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import com.benchmark.benchmark.util.BenchmarkUtil;
import java.util.HashMap;
import java.util.Map;

@RestController
public class MemoryController {

    @GetMapping("/memory/current")
    public Map<String, Object> getCurrentMemory() {
        long totalMemory = Runtime.getRuntime().totalMemory();
        long freeMemory = Runtime.getRuntime().freeMemory();
        long usedMemory = totalMemory - freeMemory;
        long maxMemory = Runtime.getRuntime().maxMemory();
        
        Map<String, Object> response = new HashMap<>();
        response.put("totalMemory", BenchmarkUtil.formatMemoryUsage(totalMemory));
        response.put("freeMemory", BenchmarkUtil.formatMemoryUsage(freeMemory));
        response.put("usedMemory", BenchmarkUtil.formatMemoryUsage(usedMemory));
        response.put("maxMemory", BenchmarkUtil.formatMemoryUsage(maxMemory));
        response.put("memoryUsagePercent", String.format("%.2f", (double) usedMemory / totalMemory * 100) + "%");

        
        return response;
    }
    
    @GetMapping("/memory/stats")
    public Map<String, Object> getMemoryStats() {
        Runtime runtime = Runtime.getRuntime();
        
        Map<String, Object> response = new HashMap<>();
        response.put("availableProcessors", runtime.availableProcessors());
        response.put("totalMemory", BenchmarkUtil.formatMemoryUsage(runtime.totalMemory()));
        response.put("freeMemory", BenchmarkUtil.formatMemoryUsage(runtime.freeMemory()));
        response.put("maxMemory", BenchmarkUtil.formatMemoryUsage(runtime.maxMemory()));
        response.put("usedMemory", BenchmarkUtil.formatMemoryUsage(runtime.totalMemory() - runtime.freeMemory()));
        
        return response;
    }
} 