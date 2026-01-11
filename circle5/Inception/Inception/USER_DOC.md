*This project has been created as part of the 42 curriculum by ssohn.*

# 사용자 문서 - Inception

이 가이드는 최종 사용자 또는 시스템 관리자로서 Inception 인프라를 사용하고 관리하는 방법을 설명합니다.

## 서비스 개요

Inception 스택은 다음을 제공합니다:

- **WordPress 웹사이트**: 완전한 기능을 갖춘 콘텐츠 관리 시스템
- **데이터베이스**: 데이터 영속성을 위한 MariaDB
- **웹 서버**: HTTPS 암호화를 지원하는 NGINX

모든 서비스는 독립된 Docker 컨테이너에서 실행되며 비공개 네트워크를 통해 통신합니다.

## 빠른 시작

### 프로젝트 시작하기

```bash
# 프로젝트 루트 디렉토리에서
make

# 또는 단계별로:
make setup    # 데이터 디렉토리 생성
make build    # Docker 이미지 빌드
make up       # 모든 서비스 시작
```

**첫 시작은 2-3분 소요**되며 다음 작업을 수행합니다:
1. WordPress 코어 파일 다운로드
2. 데이터베이스 설정
3. 관리자 및 사용자 계정 생성

### 프로젝트 중지하기

```bash
# 모든 컨테이너 중지 (데이터는 보존됨)
make down

# 또는 재빌드 없이 재시작
make restart
```

## 웹사이트 접속

### WordPress 사이트
- URL: `https://ssohn.42.fr`
- **참고**: 보안 경고가 표시됩니다 (자체 서명 인증서)
  - "고급" → "위험을 감수하고 계속" 클릭

### 관리자 패널
- URL: `https://ssohn.42.fr/wp-admin`
- 사용자명: 아래 자격 증명 섹션 참조

## 자격 증명 관리

### 위치
모든 비밀번호는 Docker secrets에 안전하게 저장됩니다:

```bash
# Secrets 위치 (gitignore됨):
secrets/db_root_password.txt       # 데이터베이스 root 비밀번호
secrets/db_password.txt            # 데이터베이스 사용자 비밀번호
secrets/wp_admin_password.txt      # WordPress 관리자 비밀번호
secrets/wp_user_password.txt       # WordPress 사용자 비밀번호
```

### 기본 계정

**WordPress 관리자:**
- 사용자명: `wpadmin`
- 이메일: `ssohn@student.42gyeongsan.kr`
- 비밀번호: `secrets/wp_admin_password.txt`에 저장

**WordPress 사용자:**
- 사용자명: `ssohn`
- 이메일: `bigsohn99@gmail.com`
- 비밀번호: `secrets/wp_user_password.txt`에 저장

### 자격 증명 확인

```bash
# 관리자 비밀번호 확인
cat secrets/wp_admin_password.txt

# 사용자 비밀번호 확인
cat secrets/wp_user_password.txt
```

### 비밀번호 변경

1. **서비스 중지**:
```bash
make down
```

2. **secret 파일 수정**:
```bash
echo "YourNewPassword123!" > secrets/wp_admin_password.txt
```

3. **기존 데이터 제거** (비밀번호 변경에 필수):
```bash
make fclean
```

4. **재시작**:
```bash
make
```

**⚠️ 경고**: `make fclean`은 게시물과 업로드를 포함한 모든 데이터를 삭제합니다!

## 서비스 상태 확인

### 실행 중인 컨테이너 보기

```bash
make ps

# 또는 docker 직접 사용
docker ps
```

예상 출력:
```
NAME        IMAGE              STATUS         PORTS
nginx       nginx:latest       Up 5 minutes   0.0.0.0:443->443/tcp
wordpress   wordpress:latest   Up 5 minutes
mariadb     mariadb:latest     Up 5 minutes   (healthy)
```

### 로그 보기

```bash
# 모든 서비스
make logs

# 특정 서비스
docker logs nginx
docker logs wordpress
docker logs mariadb
```

### 헬스 체크

```bash
# MariaDB가 정상인지 확인
docker inspect mariadb | grep -A 5 Health

# 데이터베이스 연결 테스트
docker exec mariadb mysqladmin ping -h localhost
```

## 데이터 관리

### 데이터 위치

모든 영구 데이터는 다음 위치에 저장됩니다:
```
/home/ssohn/data/
├── mariadb/       # 데이터베이스 파일
└── wordpress/     # WordPress 파일 (업로드, 테마, 플러그인)
```

### 백업

```bash
# 먼저 서비스 중지
make down

# 데이터베이스 백업
sudo tar -czf backup-db-$(date +%Y%m%d).tar.gz /home/ssohn/data/mariadb/

# WordPress 파일 백업
sudo tar -czf backup-wp-$(date +%Y%m%d).tar.gz /home/ssohn/data/wordpress/
```

### 복원

```bash
# 중지 및 정리
make fclean

# 파일 복원
sudo tar -xzf backup-db-YYYYMMDD.tar.gz -C /
sudo tar -xzf backup-wp-YYYYMMDD.tar.gz -C /

# 서비스 시작
make
```

## 문제 해결

### "데이터베이스에 연결할 수 없습니다"

1. MariaDB가 정상인지 확인:
```bash
docker ps | grep mariadb
```

2. MariaDB 로그 확인:
```bash
docker logs mariadb
```

3. 서비스 재시작:
```bash
make restart
```

### "502 Bad Gateway"

1. WordPress 컨테이너가 실행 중인지 확인:
```bash
docker ps | grep wordpress
```

2. PHP-FPM 상태 확인:
```bash
docker exec wordpress ps aux | grep php-fpm
```

3. WordPress 로그 확인:
```bash
docker logs wordpress
```

### "연결이 거부되었습니다" 또는 "사이트에 접속할 수 없습니다"

1. `/etc/hosts`에서 도메인 확인:
```bash
cat /etc/hosts | grep ssohn.42.fr
```

다음과 같이 표시되어야 합니다:
```
127.0.0.1 ssohn.42.fr
```

2. NGINX가 포트 443에서 수신 대기 중인지 확인:
```bash
docker exec nginx netstat -tuln | grep 443
```

### 데이터 디렉토리에 "권한이 거부되었습니다"

```bash
# 소유권 수정
sudo chown -R $(whoami):$(whoami) /home/ssohn/data/

# 또는 디렉토리 재생성
make fclean
make
```

### 완전 초기화

모든 것이 실패할 경우:
```bash
# 핵 옵션: 모든 것 제거
make fclean
docker system prune -a --volumes

# 처음부터 재빌드
make
```

## 유지보수

### 정기 작업

**주간:**
- 디스크 공간 확인: `df -h /home/ssohn/data/`
- 로그 검토: `make logs`
- WordPress 업데이트 (관리자 패널을 통해)

**월간:**
- 데이터 백업
- 보안 업데이트 확인
- 사용자 접근 권한 검토

### WordPress 업데이트

**관리자 패널을 통한 업데이트** (권장):
1. https://ssohn.42.fr/wp-admin 로그인
2. 대시보드 → 업데이트로 이동
3. "지금 업데이트" 클릭

**⚠️ 참고**: 컨테이너 이미지는 정적입니다. 업데이트는 데이터 볼륨에만 적용됩니다.

## 성능

### 예상 리소스 사용량

- **CPU**: 유휴 시 ~5-10%, 부하 시 30-50%
- **RAM**: 전체 컨테이너 ~300MB
- **디스크**: ~500MB-2GB (콘텐츠에 따라 증가)

### 모니터링

```bash
# 리소스 사용량
docker stats

# 디스크 사용량
du -sh /home/ssohn/data/*
```

## 지원

문제 발생 시:
1. 이 문서 확인
2. 컨테이너 로그 검토 (`make logs`)
3. 기술적 세부사항은 DEV_DOC.md 확인
4. 공식 Docker/WordPress 문서 참조

## 보안 주의사항

- ✅ 프로덕션 사용 전 기본 비밀번호 변경
- ✅ WordPress와 플러그인을 최신 상태로 유지
- ✅ 강력한 비밀번호 사용 (최소 12자, 대소문자/숫자/기호 혼합)
- ✅ 정기적인 백업
- ⚠️ 자체 서명 인증서는 개발용입니다
- ⚠️ secrets를 절대 Git에 커밋하지 마세요
