#!/bin/bash
set -e

# Docker secrets에서 비밀번호 읽기
DB_PASSWORD=$(cat /run/secrets/db_password)
WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password)
WP_USER_PASSWORD=$(cat /run/secrets/wp_user_password)

cd /var/www/html

# 포트 번호에 따라 URL 구성 (NGINX_PORT 환경 변수 사용)
if [ -z "${NGINX_PORT}" ] || [ "${NGINX_PORT}" = "443" ]; then
    SITE_URL="https://${DOMAIN_NAME}"
else
    SITE_URL="https://${DOMAIN_NAME}:${NGINX_PORT}"
fi

# WordPress가 이미 설치되어 있는지 확인
if [ ! -f wp-config.php ]; then
    # WordPress 코어 파일 다운로드
    wp core download --allow-root

    # wp-config.php 생성 (DB 연결 정보)
    wp config create \
        --dbname=${MYSQL_DATABASE} \
        --dbuser=${MYSQL_USER} \
        --dbpass=${DB_PASSWORD} \
        --dbhost=${WORDPRESS_DB_HOST} \
        --allow-root

    # MariaDB가 준비될 때까지 대기
    until wp db check --allow-root 2>/dev/null; do
        sleep 1
    done

    # WordPress 설치 (관리자 계정 생성)
    wp core install \
        --url="${SITE_URL}" \
        --title="Inception WordPress" \
        --admin_user=${WORDPRESS_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASSWORD} \
        --admin_email=${WORDPRESS_ADMIN_EMAIL} \
        --skip-email \
        --allow-root

    # 일반 사용자 계정 추가 (필수 요구사항)
    wp user create \
        ${WORDPRESS_USER} \
        ${WORDPRESS_USER_EMAIL} \
        --user_pass=${WP_USER_PASSWORD} \
        --role=author \
        --allow-root
else
    # 이미 설치된 경우, URL 업데이트
    wp option update home "${SITE_URL}" --allow-root
    wp option update siteurl "${SITE_URL}" --allow-root
fi

# 파일 권한 설정
chown -R www-data:www-data /var/www/html
chmod -R 755 /var/www/html

# PHP-FPM 실행 디렉토리 생성
mkdir -p /run/php
chown www-data:www-data /run/php

# PHP-FPM 시작 (foreground 모드, PID 1로 실행)
exec php-fpm8.2 -F
