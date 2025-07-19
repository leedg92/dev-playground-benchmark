FROM python:3.11-slim

# 성능 측정을 위한 도구 설치
RUN apt-get update && apt-get install -y curl procps gcc && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# 의존성 설치
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# 애플리케이션 코드 복사
COPY app/ ./app/

# 성능 최적화 환경변수
ENV PYTHONOPTIMIZE=1
ENV PYTHONUNBUFFERED=1

EXPOSE 8000
CMD ["uvicorn", "app.main:app", "--host", "0.0.0.0", "--port", "8000"]
