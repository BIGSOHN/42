*This project has been created as part of the 42 curriculum by ssohn.*

# 개발자 문서 - Inception

이 가이드는 개발자 관점에서 Inception 인프라를 설정, 개발 및 유지보수하는 방법을 설명합니다.

## 환경 설정

### 준비 사항

**필수 소프트웨어:**
```bash
# Docker Engine 20.10+
docker --version

# Docker Compose V2
docker compose version

# Make
make --version

# Git
git --version
```

**시스템 요구사항:**
- Linux (Ubuntu 20.04+, Debian 11+ 또는 동급)
- 2GB+ RAM
- 10GB+ 여유 디스크 공간
- Sudo 권한

### 초기 설정

1. **저장소 클론:**
```bash
git clone <repository-url>
cd Inception
```

2. **secrets 디렉토리 및 파일 생성:**
```bash
mkdir -p secrets
echo "YourRootPassword123!" > secrets/db_root_password.txt
echo "YourDBPassword456!" > secrets/db_password.txt
echo "YourAdminPassword789!" > secrets/wp_admin_password.txt
echo "YourUserPassword012!" > secrets/wp_user_password.txt
chmod 600 secrets/*.txt
```

3. **환경 설정:**
```bash
# .env 파일 복사 및 수정
vim srcs/.env

# 설정할 주요 변수:
# DOMAIN_NAME - 도메인 (기본값: ssohn.42.fr)
# MYSQL_DATABASE - 데이터베이스 이름
# MYSQL_USER - 데이터베이스 사용자
# WORDPRESS_ADMIN_USER - WP 관리자 사용자명
# WORDPRESS_USER - WP 일반 사용자
```

4. **hosts에 도메인 추가:**
```bash
echo "127.0.0.1 ssohn.42.fr" | sudo tee -a /etc/hosts
```

## 프로젝트 구조

```
Inception/
├── Makefile                      # 빌드 자동화
├── .gitignore                    # Git ignore 규칙
├── secrets/                      # Docker secrets (Git에 없음)
│   ├── db_root_password.txt     # MariaDB root 비밀번호
│   ├── db_password.txt          # MariaDB 사용자 비밀번호
│   ├── wp_admin_password.txt    # WordPress 관리자 비밀번호
│   └── wp_user_password.txt     # WordPress 사용자 비밀번호
└── srcs/
    ├── .env                      # 환경 변수 (Git에 없음)
    ├── docker-compose.yml        # 서비스 오케스트레이션
    └── requirements/             # 서비스 정의
        ├── mariadb/
        │   ├── Dockerfile       # MariaDB 이미지 빌드
        │   ├── .dockerignore
        │   ├── conf/
        │   │   └── 50-server.cnf # MariaDB 설정
        │   └── tools/
        │       └── init-db.sh   # 데이터베이스 초기화 스크립트
        ├── nginx/
        │   ├── Dockerfile       # NGINX 이미지 빌드
        │   ├── .dockerignore
        │   ├── conf/
        │   │   └── nginx.conf   # NGINX + TLS 설정
        │   └── tools/
        │       └── setup-ssl.sh # SSL 인증서 생성
        └── wordpress/
            ├── Dockerfile       # WordPress 이미지 빌드
            ├── .dockerignore
            └── tools/
                └── setup-wordpress.sh # WP 설치 스크립트
```

## 빌드 및 실행

### Makefile 명령어

```bash
# 완전한 빌드 및 시작
make                  # 다음과 동일: make setup build up

# 개별 단계
make setup           # /home/${USER}/data 디렉토리 생성
make build           # 모든 Docker 이미지 빌드
make up              # detached 모드로 컨테이너 시작
make down            # 컨테이너 중지 및 제거
make restart         # 모든 컨테이너 재시작

# 유지보수
make logs            # 모든 컨테이너의 로그 팔로우
make ps              # 실행 중인 컨테이너 표시
make clean           # 컨테이너 중지, 이미지 및 네트워크 제거
make fclean          # 데이터 볼륨 포함 전체 정리
make re              # 모든 것 재빌드 (fclean + all)
```

### 수동 Docker 명령어

```bash
# 특정 서비스 빌드
docker compose -f srcs/docker-compose.yml build mariadb

# 특정 서비스 시작
docker compose -f srcs/docker-compose.yml up -d nginx

# 특정 서비스 로그 보기
docker compose -f srcs/docker-compose.yml logs -f wordpress

# 컨테이너에서 명령 실행
docker exec -it mariadb bash
docker exec -it wordpress wp --info --allow-root

# 컨테이너 검사
docker inspect nginx
docker inspect --format='{{.State.Health.Status}}' mariadb
```

## 데이터 영속성

### 볼륨 설정

볼륨은 `/home/${USER}/data`에 bind mount를 사용합니다:

```yaml
volumes:
  mariadb_data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/${USER}/data/mariadb

  wordpress_data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/${USER}/data/wordpress
```

**호스트 위치:**
```
/home/ssohn/data/
├── mariadb/              # MariaDB 데이터 파일
│   ├── mysql/           # 시스템 데이터베이스
│   ├── wordpress/       # WordPress 데이터베이스
│   └── ...
└── wordpress/           # WordPress 파일
    ├── wp-admin/
    ├── wp-content/
    │   ├── uploads/     # 미디어 파일
    │   ├── themes/
    │   └── plugins/
    └── wp-config.php
```

### 데이터 접근

```bash
# 데이터베이스 파일 보기
ls -la /home/ssohn/data/mariadb/

# WordPress 파일 보기
ls -la /home/ssohn/data/wordpress/

# 디스크 사용량 확인
du -sh /home/ssohn/data/*
```

### 데이터 생명주기

1. **첫 실행:**
   - `make setup`이 빈 디렉토리 생성
   - 컨테이너가 첫 시작 시 초기화
   - MariaDB가 시스템 테이블 생성
   - WordPress 다운로드 및 설치

2. **이후 실행:**
   - 기존 데이터 재사용
   - 재초기화 없음
   - wp-config.php가 존재하면 WordPress 설치 스킵

3. **정리:**
   - `make down`: 컨테이너 중지, 데이터 유지
   - `make clean`: 컨테이너 + 이미지 제거, 데이터 유지
   - `make fclean`: 데이터 포함 모든 것 제거

## Docker Compose 설정

### 서비스 의존성

```yaml
wordpress:
  depends_on:
    mariadb:
      condition: service_healthy  # DB 준비 완료 대기
```

**시작 순서:**
1. MariaDB 시작
2. 헬스 체크 통과 (mysqladmin ping)
3. WordPress 시작
4. NGINX 시작 (WordPress 이후)

### 네트워크 설정

```yaml
networks:
  inception_network:
    driver: bridge
```

**서비스 탐색:**
- `mariadb` → MariaDB 컨테이너 IP로 해석
- `wordpress` → WordPress 컨테이너 IP로 해석
- `nginx` → NGINX 컨테이너 IP로 해석

**WordPress에서 연결 예시:**
```bash
WORDPRESS_DB_HOST=mariadb:3306  # IP가 아닌 서비스 이름 사용
```

### Secrets 설정

```yaml
secrets:
  db_root_password:
    file: ../secrets/db_root_password.txt
  db_password:
    file: ../secrets/db_password.txt
```

**컨테이너 내부:**
```bash
# Secrets는 다음 위치에 마운트됨:
/run/secrets/db_root_password
/run/secrets/db_password
/run/secrets/wp_admin_password
/run/secrets/wp_user_password

# 스크립트에서 읽기:
MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
```

## 서비스 상세 정보

### MariaDB

**Dockerfile 하이라이트:**
```dockerfile
FROM debian:bookworm
RUN apt-get install -y mariadb-server mariadb-client
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/
COPY tools/init-db.sh /usr/local/bin/
ENTRYPOINT ["init-db.sh"]
```

**초기화 흐름 (init-db.sh):**
1. `/var/lib/mysql/mysql` 존재 확인
2. 없으면 `mysql_install_db` 실행
3. mysqld를 임시로 시작 (네트워크 없음)
4. 데이터베이스 및 사용자 생성
5. 임시 mysqld 중지
6. PID 1로 최종 mysqld 시작

**설정 (50-server.cnf):**
```ini
[mysqld]
bind-address = 0.0.0.0  # 모든 인터페이스에서 수신 (Docker 네트워크)
port = 3306
datadir = /var/lib/mysql
```

**헬스 체크:**
```yaml
healthcheck:
  test: ["CMD", "mysqladmin", "ping", "-h", "localhost"]
  interval: 10s
  timeout: 5s
  retries: 5
```

### WordPress

**Dockerfile 하이라이트:**
```dockerfile
FROM debian:bookworm
RUN apt-get install -y php8.2-fpm php8.2-mysql curl
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
COPY tools/setup-wordpress.sh /usr/local/bin/
ENTRYPOINT ["setup-wordpress.sh"]
```

**설치 흐름 (setup-wordpress.sh):**
1. `wp-config.php` 존재 확인
2. 없으면:
   - WP-CLI로 WordPress 코어 다운로드
   - wp-config.php 생성 (데이터베이스 연결)
   - 데이터베이스 가용성 대기
   - WordPress 설치 (관리자 생성)
   - 추가 사용자 생성
3. 권한 설정
4. PID 1로 PHP-FPM 시작

**WP-CLI 사용:**
```bash
# 컨테이너 내부
docker exec wordpress wp --info --allow-root
docker exec wordpress wp user list --allow-root
docker exec wordpress wp plugin list --allow-root
```

### NGINX

**Dockerfile 하이라이트:**
```dockerfile
FROM debian:bookworm
RUN apt-get install -y nginx openssl
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/setup-ssl.sh /usr/local/bin/
RUN /usr/local/bin/setup-ssl.sh
CMD ["nginx", "-g", "daemon off;"]
```

**TLS 설정 (nginx.conf):**
```nginx
server {
    listen 443 ssl;
    ssl_certificate /etc/nginx/ssl/nginx.crt;
    ssl_certificate_key /etc/nginx/ssl/nginx.key;
    ssl_protocols TLSv1.2 TLSv1.3;  # TLS 1.0/1.1 없음

    location ~ \.php$ {
        fastcgi_pass wordpress:9000;  # 포트 9000의 PHP-FPM
    }
}
```

**SSL 인증서 생성 (setup-ssl.sh):**
```bash
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/CN=ssohn.42.fr"
```

## 개발 워크플로우

### 변경사항 적용

1. **설정 파일 수정** (conf/, tools/)
2. **영향받는 서비스 재빌드:**
```bash
docker compose -f srcs/docker-compose.yml build nginx
```
3. **서비스 재시작:**
```bash
docker compose -f srcs/docker-compose.yml up -d nginx
```
4. **변경사항 테스트:**
```bash
docker logs nginx
curl -k https://ssohn.42.fr
```

### 테스트

```bash
# 데이터베이스 연결 테스트
docker exec mariadb mysql -u wpuser -p$(cat secrets/db_password.txt) -e "SHOW DATABASES;"

# PHP-FPM 테스트
docker exec wordpress php-fpm8.2 -t

# NGINX 설정 테스트
docker exec nginx nginx -t

# TLS 테스트
openssl s_client -connect localhost:443 -tls1_2
```

### 디버깅

```bash
# 컨테이너 셸 진입
docker exec -it mariadb bash
docker exec -it wordpress bash
docker exec -it nginx bash

# 프로세스 트리 확인
docker exec mariadb ps aux

# 네트워크 연결성
docker exec wordpress ping mariadb
docker exec nginx nc -zv wordpress 9000

# 파일 권한
docker exec wordpress ls -la /var/www/html
```

## 모범 사례

### 보안

- ✅ secrets를 절대 Git에 커밋하지 않기
- ✅ 강력한 비밀번호 사용 (12자 이상, 대소문자/숫자/기호 혼합)
- ✅ 환경 변수가 아닌 `/run/secrets`의 Secrets 사용
- ✅ 최소한의 베이스 이미지 (debian:bookworm)
- ✅ 가능한 곳에서 non-root 실행 (www-data, mysql 사용자)

### 성능

- ✅ 멀티 스테이지 빌드 (여기서는 불필요, 이미지가 단순함)
- ✅ 레이어 캐싱 (Dockerfile 끝에 COPY)
- ✅ 불필요한 파일 제외를 위한 `.dockerignore`
- ✅ apt 캐시 정리: `rm -rf /var/lib/apt/lists/*`

### 안정성

- ✅ 중요 서비스에 헬스 체크
- ✅ 자동 복구를 위한 `restart: unless-stopped`
- ✅ `condition: service_healthy`와 함께 `depends_on`
- ✅ 멱등성 있는 초기화 스크립트 (이미 초기화되었는지 확인)
- ✅ 스크립트에서 `exec`로 메인 프로세스를 셸로 교체 (PID 1)

## 문제 해결

### 빌드 이슈

```bash
# 빌드 캐시 정리
docker builder prune

# 캐시 없이 빌드
docker compose -f srcs/docker-compose.yml build --no-cache

# Docker 디스크 사용량 확인
docker system df
```

### 런타임 이슈

```bash
# 컨테이너 헬스 확인
docker inspect --format='{{.State.Health.Status}}' mariadb

# 전체 컨테이너 로그 보기
docker logs --tail 100 wordpress

# 네트워크 연결성 확인
docker network inspect inception_inception_network
```

### 권한 이슈

```bash
# 데이터 디렉토리 소유권 수정
sudo chown -R $(whoami):$(whoami) /home/ssohn/data/

# 컨테이너 내부에서 파일 소유권 확인
docker exec wordpress ls -ln /var/www/html/
```

## 일반적인 작업

### WordPress 버전 업데이트

현재 WordPress.org에서 최신 버전 사용. 버전을 고정하려면:

```bash
# setup-wordpress.sh에서 변경:
wp core download --allow-root
# 다음으로:
wp core download --version=6.4 --allow-root
```

### 도메인 이름 변경

1. `srcs/.env` 수정:
```bash
DOMAIN_NAME=newdomain.42.fr
```

2. `/etc/hosts` 업데이트
3. NGINX 재빌드 (SSL 인증서용):
```bash
make fclean
make
```

### 새 서비스 추가

1. 디렉토리 생성: `srcs/requirements/newservice/`
2. Dockerfile, conf/, tools/ 추가
3. `docker-compose.yml` 업데이트
4. 필요시 네트워크와 볼륨에 추가

## 참고 자료

- [Docker 모범 사례](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
- [Docker Compose 문서](https://docs.docker.com/compose/)
- [MariaDB 문서](https://mariadb.com/kb/en/)
- [WordPress 개발자 문서](https://developer.wordpress.org/)
- [NGINX 관리자 가이드](https://nginx.org/en/docs/)
- [WP-CLI 핸드북](https://make.wordpress.org/cli/handbook/)
