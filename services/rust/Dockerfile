FROM rust:1.70-slim AS builder

WORKDIR /app
COPY Cargo.toml Cargo.lock ./
COPY src ./src

# 성능 최적화 빌드
RUN cargo build --release

FROM debian:bookworm-slim
# 성능 측정을 위한 도구 설치
RUN apt-get update && apt-get install -y wget curl procps && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/target/release/benchmark-rust ./

EXPOSE 8080
CMD ["./benchmark-rust"]
