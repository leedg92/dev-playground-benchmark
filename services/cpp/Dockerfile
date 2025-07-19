FROM gcc:11-slim AS builder

# 필요한 도구 설치
RUN apt-get update && apt-get install -y cmake build-essential && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY CMakeLists.txt .
COPY src ./src

# 성능 최적화 빌드
RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make

FROM debian:bookworm-slim
# 성능 측정을 위한 도구 설치
RUN apt-get update && apt-get install -y wget curl procps && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/benchmark-cpp ./

EXPOSE 8080
CMD ["./benchmark-cpp"]
