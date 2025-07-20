FROM openjdk:17-jdk-slim AS builder

WORKDIR /app
COPY pom.xml .
COPY src ./src

# Maven 설치 및 빌드
RUN apt-get update && apt-get install -y maven && \
    mvn clean package -DskipTests && \
    rm -rf ~/.m2/repository

FROM openjdk:17-jdk-slim

# 성능 측정을 위한 도구 설치
RUN apt-get update && apt-get install -y curl procps && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/target/*.jar app.jar

# 성능 최적화 JVM 옵션
ENV JAVA_OPTS="-server -XX:+UseG1GC -XX:+UseStringDeduplication"

EXPOSE 8080
ENTRYPOINT ["sh", "-c", "java $JAVA_OPTS -jar app.jar"]
