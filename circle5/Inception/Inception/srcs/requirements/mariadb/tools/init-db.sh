#!/bin/bash
set -e

# Docker secrets에서 비밀번호 읽기
MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
MYSQL_PASSWORD=$(cat /run/secrets/db_password)

# 첫 실행인지 확인: mysql 시스템 DB가 없으면 초기화 필요
if [ ! -d "/var/lib/mysql/mysql" ]; then
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

# DB 설정을 위해 임시로 MariaDB 시작 (네트워크 비활성화)
mysqld --user=mysql --skip-networking --skip-grant-tables &
pid="$!"

# MariaDB가 완전히 시작될 때까지 대기
for i in {30..0}; do
    if mysqladmin ping --silent; then
        break
    fi
    sleep 1
done

if [ "$i" = 0 ]; then
    exit 1
fi

# 데이터베이스가 이미 존재하는지 확인
if ! mysql -u root -e "USE ${MYSQL_DATABASE}" 2>/dev/null; then
    # 첫 실행: root 비밀번호 설정, DB 및 사용자 생성
    mysql -u root << EOF
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF
fi

# 임시 MariaDB 프로세스 종료
kill -TERM "$pid"
wait "$pid"

# 정식으로 MariaDB 시작 (PID 1로 실행)
exec mysqld --user=mysql --datadir=/var/lib/mysql