# Makefile for Algorithm Performance Benchmark System
# 프로젝트: 다중 언어 알고리즘 성능 벤치마크

# 변수 정의
COMPOSE_FILE = docker-compose.yaml
SERVICES = java-service python-service go-service rust-service cpp-service nodejs-service
IMAGE_PREFIX = dev-playground-benchmark
PORTS = 8021 8022 8023 8024 8025 8026

# 기본 타겟 (help 출력)
.DEFAULT_GOAL := help

# PHONY 타겟 선언
.PHONY: help setup install build dev dev-build dev-logs stop clean logs shell health-check test-all test-language benchmark-all status restart clean-all

# 도움말 출력
help:
	@echo "🚀 다중 언어 알고리즘 성능 벤치마크 시스템 개발 명령어"
	@echo ""
	@echo "📦 설치 및 설정:"
	@echo "  make setup          - 프로젝트 초기 설정 (전체 시스템 구축)"
	@echo "  make install        - 호스트 언어 환경 설치 (brew)"
	@echo ""
	@echo "🏗️  빌드:"
	@echo "  make build          - 모든 언어 Docker 이미지 빌드"
	@echo "  make build-nc       - 모든 언어 Docker 이미지 빌드 (캐시 없이)"
	@echo "  make build-java     - Java 서비스만 빌드"
	@echo "  make build-python   - Python 서비스만 빌드"
	@echo "  make build-go       - Go 서비스만 빌드"
	@echo "  make build-rust     - Rust 서비스만 빌드"
	@echo "  make build-cpp      - C++ 서비스만 빌드"
	@echo "  make build-nodejs   - Node.js 서비스만 빌드"
	@echo ""
	@echo "🔧 개발 환경:"
	@echo "  make dev            - 모든 서비스 시작 (백그라운드)"
	@echo "  make dev-build      - 빌드 후 모든 서비스 시작"
	@echo "  make dev-logs       - 모든 서비스 로그 실시간 확인"
	@echo ""
	@echo "🧪 테스트 및 벤치마크:"
	@echo "  make health-check   - 모든 서비스 상태 확인"
	@echo "  make test-all       - 모든 언어 기본 테스트"
	@echo "  make test-java      - Java 서비스 테스트"
	@echo "  make test-python    - Python 서비스 테스트"
	@echo "  make benchmark-fib  - 피보나치 벤치마크 (모든 언어)"
	@echo "  make benchmark-sort - 정렬 벤치마크 (모든 언어)"
	@echo ""
	@echo "📋 모니터링:"
	@echo "  make logs           - 모든 서비스 로그 확인"
	@echo "  make logs-java      - Java 서비스 로그 확인"
	@echo "  make logs-python    - Python 서비스 로그 확인"
	@echo "  make logs-go        - Go 서비스 로그 확인"
	@echo "  make logs-rust      - Rust 서비스 로그 확인"
	@echo "  make logs-cpp       - C++ 서비스 로그 확인"
	@echo "  make logs-nodejs    - Node.js 서비스 로그 확인"
	@echo "  make status         - 컨테이너 상태 확인"
	@echo ""
	@echo "🛠️  유틸리티:"
	@echo "  make shell-java     - Java 컨테이너 내부 접속"
	@echo "  make shell-python   - Python 컨테이너 내부 접속"
	@echo "  make stop           - 모든 서비스 중지"
	@echo "  make restart        - 모든 서비스 재시작"
	@echo "  make clean          - 컨테이너 및 이미지 정리"
	@echo "  make clean-all      - 모든 Docker 리소스 정리"

# 프로젝트 초기 설정
setup:
	@echo "🔧 프로젝트 초기 설정 중..."
	@echo "🏗️  Docker 이미지 빌드 중..."
	docker-compose build
	@echo "🚀 모든 서비스 시작 중..."
	docker-compose up -d
	@echo "⏳ 서비스 준비 중..."
	sleep 15
	@echo "🏥 서비스 상태 확인 중..."
	$(MAKE) health-check
	@echo "✅ 프로젝트 설정 완료!"
	@echo "🌐 서비스 포트:"
	@echo "   Java:    http://localhost:8021"
	@echo "   Python:  http://localhost:8022"
	@echo "   Go:      http://localhost:8023"
	@echo "   Rust:    http://localhost:8024"
	@echo "   C++:     http://localhost:8025"
	@echo "   Node.js: http://localhost:8026"

# 호스트 언어 환경 설치
install:
	@echo "📦 호스트 언어 환경 설치 중..."
	@echo "☕ Java, Python, Go, Rust, Node.js 설치..."
	brew install openjdk@17 python@3.11 go rust node
	@echo "🔨 C++ 개발 도구 설치..."
	xcode-select --install || echo "Xcode Command Line Tools 이미 설치됨"
	@echo "🛠️  빌드 도구 설치..."
	brew install maven cmake
	@echo "✅ 모든 언어 환경 설치 완료!"

# 모든 언어 Docker 이미지 빌드
build:
	@echo "🏗️  모든 언어 Docker 이미지 빌드 중..."
	docker-compose build

# 캐시 없이 빌드
build-nc:
	@echo "🏗️  모든 언어 Docker 이미지 빌드 중 (캐시 없이)..."
	docker-compose build --no-cache

# 개별 언어 빌드 타겟
build-java:
	@echo "☕ Java 서비스 빌드 중..."
	docker-compose build java-service

build-python:
	@echo "🐍 Python 서비스 빌드 중..."
	docker-compose build python-service

build-go:
	@echo "🐹 Go 서비스 빌드 중..."
	docker-compose build go-service

build-rust:
	@echo "🦀 Rust 서비스 빌드 중..."
	docker-compose build rust-service

build-cpp:
	@echo "⚡ C++ 서비스 빌드 중..."
	docker-compose build cpp-service

build-nodejs:
	@echo "🟢 Node.js 서비스 빌드 중..."
	docker-compose build nodejs-service

# 개발 서버 시작 (백그라운드)
dev:
	@echo "🚀 모든 서비스 시작 중 (백그라운드)..."
	docker-compose up -d
	@echo "✅ 모든 서비스가 시작되었습니다!"
	@echo "🌐 서비스 포트: 8021-8026"
	@echo "💡 로그를 보려면 'make dev-logs' 를 실행하세요"

# 빌드 후 개발 서버 시작
dev-build:
	@echo "🏗️  빌드 후 모든 서비스 시작 중..."
	docker-compose up -d --build
	@echo "✅ 모든 서비스가 시작되었습니다!"

# 모든 서비스 로그 실시간 확인
dev-logs:
	@echo "📋 모든 서비스 로그 실시간 확인 중..."
	@echo "💡 Ctrl+C로 중지할 수 있습니다"
	docker-compose logs -f

# 서비스 상태 확인
health-check:
	@echo "🏥 모든 서비스 상태 확인 중..."
	@for port in $(PORTS); do \
		echo "🔍 포트 $$port 확인 중..."; \
		curl -f http://localhost:$$port/health || echo "❌ 포트 $$port 응답 없음"; \
	done

# 모든 언어 기본 테스트
test-all:
	@echo "🧪 모든 언어 기본 테스트 실행 중..."
	@for port in $(PORTS); do \
		echo "🔍 포트 $$port 테스트 중..."; \
		curl -f http://localhost:$$port/api/test || echo "❌ 포트 $$port 테스트 실패"; \
	done

# Java 서비스 테스트
test-java:
	@echo "☕ Java 서비스 테스트 중..."
	curl -f http://localhost:8021/api/test

# Python 서비스 테스트
test-python:
	@echo "🐍 Python 서비스 테스트 중..."
	curl -f http://localhost:8022/api/test

# 피보나치 벤치마크
benchmark-fib:
	@echo "🧮 피보나치 벤치마크 실행 중..."
	@for port in $(PORTS); do \
		echo "🔍 포트 $$port 피보나치(35) 실행 중..."; \
		curl -X POST http://localhost:$$port/api/benchmark/fibonacci -d '{"input": 35}' -H "Content-Type: application/json"; \
	done

# 정렬 벤치마크
benchmark-sort:
	@echo "📊 정렬 벤치마크 실행 중..."
	@for port in $(PORTS); do \
		echo "🔍 포트 $$port 정렬(100000) 실행 중..."; \
		curl -X POST http://localhost:$$port/api/benchmark/sort -d '{"input": 100000}' -H "Content-Type: application/json"; \
	done

# 로그 확인 타겟들
logs:
	@echo "📋 모든 서비스 로그 확인 중..."
	docker-compose logs

logs-java:
	@echo "📋 Java 서비스 로그 확인 중..."
	docker-compose logs java-service

logs-python:
	@echo "📋 Python 서비스 로그 확인 중..."
	docker-compose logs python-service

logs-go:
	@echo "📋 Go 서비스 로그 확인 중..."
	docker-compose logs go-service

logs-rust:
	@echo "📋 Rust 서비스 로그 확인 중..."
	docker-compose logs rust-service

logs-cpp:
	@echo "📋 C++ 서비스 로그 확인 중..."
	docker-compose logs cpp-service

logs-nodejs:
	@echo "📋 Node.js 서비스 로그 확인 중..."
	docker-compose logs nodejs-service

# 컨테이너 상태 확인
status:
	@echo "📊 컨테이너 상태 확인 중..."
	docker-compose ps

# 쉘 접속 타겟들
shell-java:
	@echo "🐚 Java 컨테이너 내부 접속 중..."
	docker-compose exec java-service sh

shell-python:
	@echo "🐚 Python 컨테이너 내부 접속 중..."
	docker-compose exec python-service sh

# 모든 서비스 중지
stop:
	@echo "⏹️  모든 서비스 중지 중..."
	docker-compose down
	@echo "✅ 모든 서비스가 중지되었습니다"

# 모든 서비스 재시작
restart:
	@echo "🔄 모든 서비스 재시작 중..."
	docker-compose restart
	@echo "✅ 모든 서비스가 재시작되었습니다"

# 컨테이너 및 이미지 정리
clean:
	@echo "🧹 컨테이너 및 이미지 정리 중..."
	docker-compose down --rmi local --volumes --remove-orphans
	@echo "✅ 정리 완료!"

# 모든 Docker 리소스 정리 (주의: 다른 프로젝트에도 영향)
clean-all:
	@echo "⚠️  모든 Docker 리소스 정리 중..."
	@echo "이 명령은 다른 프로젝트에도 영향을 줄 수 있습니다."
	@read -p "계속하시겠습니까? (y/N): " confirm && [ "$$confirm" = "y" ]
	docker system prune -a --volumes
	@echo "✅ 모든 Docker 리소스가 정리되었습니다"
