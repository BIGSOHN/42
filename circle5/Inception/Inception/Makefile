# Variables
COMPOSE_FILE = srcs/docker-compose.yml
DATA_DIR = $(HOME)/data

.PHONY: all build up down clean fclean re logs ps setup

all: setup build up

# 데이터 디렉토리 생성
setup:
	@mkdir -p $(DATA_DIR)/mariadb
	@mkdir -p $(DATA_DIR)/wordpress

# Docker 이미지 빌드
build:
	@docker compose -f $(COMPOSE_FILE) build

# 컨테이너 시작
up:
	@docker compose -f $(COMPOSE_FILE) up -d

# 컨테이너 중지
down:
	@docker compose -f $(COMPOSE_FILE) down

# 컨테이너 재시작
restart: down up

# 로그 확인
logs:
	@docker compose -f $(COMPOSE_FILE) logs -f

# 컨테이너 상태 확인
ps:
	@docker compose -f $(COMPOSE_FILE) ps

# 컨테이너 정지 및 삭제
clean: down
	@docker compose -f $(COMPOSE_FILE) down -v --rmi all

# 완전 초기화 (데이터 포함)
fclean: clean
	@sudo rm -rf $(DATA_DIR)/mariadb/*
	@sudo rm -rf $(DATA_DIR)/wordpress/*

# 재빌드
re: fclean all

