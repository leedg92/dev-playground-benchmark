FROM node:18-alpine

# 성능 측정을 위한 도구 설치
RUN apk --no-cache add wget curl procps

WORKDIR /app

# 의존성 설치
COPY package*.json ./
RUN npm ci --only=production

# 애플리케이션 코드 복사
COPY src ./src

# 성능 최적화 환경변수
ENV NODE_ENV=production
ENV NODE_OPTIONS=--max-old-space-size=1800

EXPOSE 8080
CMD ["node", "src/main.js"]
