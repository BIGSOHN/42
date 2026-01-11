*This project has been created as part of the 42 curriculum by ssohn.*

# Inception

Docker Compose를 사용하여 완전한 웹 인프라를 구축하는 시스템 관리 프로젝트입니다.

## 프로젝트 설명

이 프로젝트는 다음과 같은 멀티 컨테이너 Docker 애플리케이션을 구현합니다:
- **NGINX** - TLS 1.2/1.3 암호화를 지원하는 웹 서버
- **WordPress** - 콘텐츠 관리를 위한 PHP-FPM 기반 WordPress
- **MariaDB** - 데이터 영속성을 위한 데이터베이스

인프라는 Docker 모범 사례를 따라 설계되었으며, 각 서비스는 독립된 컨테이너에서 실행되고, 사용자 정의 Docker 네트워크로 연결되며, 안전한 자격 증명 관리를 위해 Docker secrets를 사용합니다.

## 아키텍처

```
┌─────────────────────────────────────────┐
│          컴퓨터 호스트                    │
│  ┌───────────────────────────────────┐  │
│  │   Docker 네트워크 (bridge)         │  │
│  │  ┌──────┐  ┌──────────┐  ┌────┐  │  │
│  │  │ NGINX│─→│WordPress │←─│ DB │  │  │
│  │  │ :443 │  │ +PHP-FPM │  │    │  │  │
│  │  └──┬───┘  └────┬─────┘  └─┬──┘  │  │
│  └─────┼──────────┼──────────┼──────┘  │
│        │          │          │          │
│    ┌───▼──────┐  ┌▼─────────▼┐         │
│    │ WP 파일  │  │ 데이터베이스│         │
│    │  볼륨    │  │   볼륨     │         │
│    └──────────┘  └───────────┘         │
└─────────────────────────────────────────┘
```

## 사용 방법

### 준비사항
- Docker Engine 20.10+
- Docker Compose V2
- Make
- 볼륨 생성을 위한 sudo 권한

### 설치

1. 레포지토리 클론:
```bash
git clone <repository-url>
cd Inception
```

2. 환경 설정:
```bash
# srcs/.env 파일 설정
vim srcs/.env

# secrets가 올바르게 설정되었는지 확인
ls -l secrets/
```

3. hosts 파일에 도메인 추가:
```bash
echo "127.0.0.1 ssohn.42.fr" | sudo tee -a /etc/hosts
```

4. 인프라 빌드 및 시작:
```bash
make
```

5. 웹사이트 접속:
- WordPress: https://ssohn.42.fr
- 관리자 패널: https://ssohn.42.fr/wp-admin

### 사용 가능한 명령어

```bash
make          # 설정, 빌드, 모든 컨테이너 시작
make build    # Docker 이미지 빌드
make up       # 컨테이너 시작
make down     # 컨테이너 중지
make restart  # 컨테이너 재시작
make logs     # 컨테이너 로그 보기
make ps       # 컨테이너 상태 확인
make clean    # 컨테이너와 이미지 제거
make fclean   # 데이터 볼륨 포함 전체 정리
make re       # 처음부터 다시 빌드
```

## 기술적 선택

### 가상 머신 vs Docker

| 측면 | 가상 머신 | Docker (선택) |
|------|----------|--------------|
| **리소스 사용** | 무거움 (전체 OS) | 경량 (커널 공유) |
| **시작 시간** | 수 분 | 수 초 |
| **격리** | 완전 격리 | 프로세스 수준 |
| **사용 사례** | OS 전체 격리 | 애플리케이션 격리 |

**선택 이유**: Docker는 웹 서비스에 충분한 격리를 제공하면서도 더 효율적이고 배포가 빠릅니다.

### 환경변수 vs Docker Secrets

| 측면 | 환경 변수 | Docker Secrets (선택) |
|------|----------|---------------------|
| **보안** | .env에 평문 저장 | 암호화된 상태로 저장 |
| **저장소** | 파일/환경 변수 | tmpfs의 /run/secrets |
| **Git 안전성** | gitignore 필요 | 파일시스템에 도달 안 함 |
| **생명주기** | 영구적 | 임시적 |

**선택 이유**: Docker secrets는 암호화된 형태로 자격 증명을 저장하고, 런타임에만 인증된 컨테이너에 노출하여 더 나은 보안을 제공합니다.

### Host 네트워크 vs Docker 네트워크

| 측면 | Host 네트워크 | Docker 네트워크 (선택) |
|------|-------------|---------------------|
| **격리** | 없음 | 완전한 컨테이너 격리 |
| **포트 충돌** | 가능 | 방지됨 |
| **보안** | 낮음 | 높음 |
| **서비스 탐색** | 수동 | 자동 DNS |

**선택 이유**: 사용자 정의 브릿지 네트워크는 격리를 제공하고 자동 서비스 탐색을 지원합니다 (컨테이너가 이름으로 서로 접근 가능).

### Docker 볼륨 vs Bind Mounts

| 측면 | Bind Mounts (선택) | Docker 볼륨 |
|------|------------------|-------------|
| **제어** | 전체 경로 제어 | Docker가 관리 |
| **백업** | 쉬움 (알려진 위치) | docker 명령 필요 |
| **이식성** | 경로 의존적 | 완전 이식 가능 |
| **검증** | PDF에 명시적 | 암묵적 |

**선택 이유**: `/home/${USER}/data`의 Bind mounts는 명시적 데이터 위치에 대한 PDF 요구사항을 충족하며 백업과 검사를 위한 쉬운 접근을 제공합니다.

## 참고 자료

### 공식 문서
- [Docker 문서](https://docs.docker.com/)
- [Docker Compose 레퍼런스](https://docs.docker.com/compose/compose-file/)
- [NGINX 문서](https://nginx.org/en/docs/)
- [WordPress 개발자 리소스](https://developer.wordpress.org/)
- [MariaDB 지식 베이스](https://mariadb.com/kb/en/)

### 기술 참고 자료
- [Dockerfile 모범 사례](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
- [Docker 보안](https://docs.docker.com/engine/security/)
- [TLS 설정](https://ssl-config.mozilla.org/)
- [PHP-FPM 설정](https://www.php.net/manual/en/install.fpm.configuration.php)

### 튜토리얼
- [Docker 네트워킹 튜토리얼](https://docs.docker.com/network/network-tutorial-standalone/)
- [Docker로 WordPress 설치](https://developer.wordpress.org/advanced-administration/before-install/howto-install/)
- [MariaDB Docker 설정](https://mariadb.com/kb/en/installing-and-using-mariadb-via-docker/)

## AI 사용

AI 도구(Claude, ChatGPT)는 다음 용도로 사용되었습니다:
- **문서화**: 초기 README 구조와 마크다운 형식 생성
- **문제 해결**: Docker 네트워킹 이슈와 권한 문제 디버깅
- **모범 사례**: Docker secrets 구현과 TLS 설정 이해
- **코드 리뷰**: 보안 취약점과 엣지 케이스를 위한 셸 스크립트 검토

모든 AI 생성 콘텐츠는:
- 신중하게 검토되고 테스트됨
- 프로젝트 요구사항에 맞게 수정됨
- 공식 문서와 대조 검증됨
- 구현 전 완전히 이해됨

**참고**: 핵심 구현 로직, 아키텍처 결정, Dockerfile 설정은 개념 이해 후 수동으로 작성되었습니다.

## 프로젝트 구조

```
Inception/
├── Makefile                  # 빌드 자동화
├── secrets/                  # Docker secrets (gitignore됨)
│   ├── db_root_password.txt
│   ├── db_password.txt
│   ├── wp_admin_password.txt
│   └── wp_user_password.txt
└── srcs/
    ├── .env                  # 환경 변수
    ├── docker-compose.yml    # 서비스 오케스트레이션
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── 50-server.cnf
        │   └── tools/
        │       └── init-db.sh
        ├── nginx/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── nginx.conf
        │   └── tools/
        │       └── setup-ssl.sh
        └── wordpress/
            ├── Dockerfile
            └── tools/
                └── setup-wordpress.sh
```

## 보안 참고사항

- 모든 비밀번호는 Docker secrets를 통해 관리됩니다
- TLS 1.2/1.3만 사용
- 자체 서명 인증서 사용
- Secrets는 절대 Git에 커밋되지 않습니다
- `.env` 파일은 gitignore됩니다
- 데이터베이스는 Docker 네트워크에서만 접근 가능합니다

## 작성자

42 Inception 프로젝트를 위해 **ssohn**이 작성했습니다.
