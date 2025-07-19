# dev-playground-benchmark

> 다중 프로그래밍 언어 알고리즘 성능 벤치마크 - 마이크로서비스 아키텍처 언어별 성능 비교 백엔드

## 📋 프로젝트 개요

이 프로젝트는 **6개 프로그래밍 언어에서 동일한 알고리즘을 실행하여 성능을 비교**하는 벤치마크 시스템의 백엔드입니다. 
각 언어별로 독립적인 마이크로서비스를 구성하고, 실행 시간과 메모리 사용량을 측정하여 언어별 성능 특성을 분석할 수 있습니다.

### 주요 특징

- 🚀 **6개 언어 지원** - Java, Python, Go, Rust, C++, Node.js 성능 비교
- 🧮 **다양한 알고리즘** - 피보나치, 대용량 정렬, 소수 찾기, 행렬 곱셈
- 📊 **실시간 성능 측정** - 실행 시간, 메모리 사용량, CPU 사용률 추적
- 🔄 **순차/병렬 실행** - 메모리 최적화를 위한 실행 방식 선택
- 🎯 **타임아웃 보호** - 무한 실행 방지 안전장치
- 🐳 **컨테이너 격리** - 언어별 독립적인 실행 환경

## 🛠 기술 스택

### 언어/프레임워크 별 마이크로서비스
- **Java**: Spring Boot
- **Python**: FastAPI
- **Go**: Gin Framework
- **Rust**: Actix-web
- **C++**: Crow Framework
- **Node.js**: Fastify

### 인프라
- **Containerization**: Docker & Docker Compose
- **Orchestration**: 멀티 서비스 관리
- **Memory Management**: 컨테이너별 2GB 할당
- **Network**: Docker 내부 네트워크

## 🧮 지원 알고리즘

### 수학적 연산
- **피보나치 수열** - 재귀 vs 동적계획법 (입력: 30-45)
- **팩토리얼 계산** - 큰 수 연산 (입력: 1000-10000)
- **소수 찾기** - 에라토스테네스의 체 (범위: 1-10,000,000)

### 데이터 처리
- **대용량 배열 정렬** - 퀵소트/머지소트 (크기: 100만-1000만개)
- **행렬 곱셈** - 2차원 배열 연산 (크기: 500x500-2000x2000)
- **해시맵 연산** - 대량 삽입/검색 (100만-1000만개)

### 문자열 처리
- **패턴 매칭** - 대용량 텍스트 검색
- **문자열 조작** - 연결, 분할, 치환

## 🚀 시작하기

### 환경 요구사항
- Docker & Docker Compose
- 16GB+ RAM (권장: 24GB+)

### 설치 및 실행

1. **저장소 클론**
```bash
git clone <repository-url>
cd dev-playground-benchmark
```

2. **전체 시스템 구축**
```bash
# 모든 언어별 컨테이너 빌드 및 실행
make setup

# 개발 환경 시작
make dev
```

3. **API 엔드포인트**
```
Java API: http://localhost:8021
Python API: http://localhost:8022
Go API: http://localhost:8023
Rust API: http://localhost:8024
C++ API: http://localhost:8025
Node.js API: http://localhost:8026
```

## 💡 사용법

### 개발 환경 관리
```bash
# 전체 시스템 상태 확인
make status

# 특정 언어 서비스 로그 확인
make logs-java       # Java 서비스 로그
make logs-python     # Python 서비스 로그
make logs-go         # Go 서비스 로그
make logs-c++        # C++ 서비스 로그
make logs-js         # node.js 서비스 로그

# 서비스 재시작
make restart

# 전체 시스템 정리
make clean
```
