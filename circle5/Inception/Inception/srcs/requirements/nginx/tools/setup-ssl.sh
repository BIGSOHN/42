#!/bin/bash

# SSL 인증서 디렉토리 생성
mkdir -p /etc/nginx/ssl

# 자체 서명 SSL 인증서 생성 (TLSv1.2/TLSv1.3용)
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=KR/ST=Gyeongbuk/L=Gyeongsan/O=42Gyeongsan/OU=ssohn/CN=ssohn.42.fr"

# 인증서 파일 권한 설정
chmod 600 /etc/nginx/ssl/nginx.key
chmod 644 /etc/nginx/ssl/nginx.crt
