# Variables
COMPOSE_FILE = srcs/docker-compose.yml
ENV_FILE = srcs/.env
DATA_DIR = $(HOME)/data
USER = $(shell whoami)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

.PHONY: all build up down clean fclean re logs ps setup help

all: setup build up

# 데이터 디렉토리 생성
setup:
	@echo "$(YELLOW)Creating data directories...$(NC)"
	@mkdir -p $(DATA_DIR)/mariadb
	@mkdir -p $(DATA_DIR)/wordpress
	@echo "$(GREEN)Data directories created at $(DATA_DIR)$(NC)"

# Docker 이미지 빌드
build:
	@echo "$(YELLOW)Building Docker images...$(NC)"
	@docker compose -f $(COMPOSE_FILE) build
	@echo "$(GREEN)Build completed!$(NC)"

# 컨테이너 시작
up:
	@echo "$(YELLOW)Starting containers...$(NC)"
	@docker compose -f $(COMPOSE_FILE) up -d
	@echo "$(GREEN)Containers started!$(NC)"
	@echo "$(BLUE)========================================$(NC)"
	@echo "$(GREEN)Access WordPress at: https://$(USER).42.fr$(NC)"
	@echo "$(BLUE)========================================$(NC)"

# 컨테이너 중지
down:
	@echo "$(YELLOW)Stopping containers...$(NC)"
	@docker compose -f $(COMPOSE_FILE) down
	@echo "$(GREEN)Containers stopped!$(NC)"

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
	@echo "$(YELLOW)Removing containers, networks, and images...$(NC)"
	@docker compose -f $(COMPOSE_FILE) down -v --rmi all
	@echo "$(GREEN)Cleanup completed!$(NC)"

# 완전 초기화 (데이터 포함)
fclean: clean
	@echo "$(RED)Removing all data...$(NC)"
	@sudo rm -rf $(DATA_DIR)/mariadb/*
	@sudo rm -rf $(DATA_DIR)/wordpress/*
	@echo "$(GREEN)Full cleanup completed!$(NC)"

# 재빌드
re: fclean all

# 도움말
help:
	@echo "$(BLUE)========================================$(NC)"
	@echo "$(BLUE)Inception Project - Available Commands$(NC)"
	@echo "$(BLUE)========================================$(NC)"
	@echo "  $(GREEN)make$(NC) or $(GREEN)make all$(NC)    - Build and start all containers"
	@echo "  $(GREEN)make build$(NC)          - Build Docker images"
	@echo "  $(GREEN)make up$(NC)             - Start containers"
	@echo "  $(GREEN)make down$(NC)           - Stop containers"
	@echo "  $(GREEN)make restart$(NC)        - Restart containers"
	@echo "  $(GREEN)make logs$(NC)           - Show container logs"
	@echo "  $(GREEN)make ps$(NC)             - Show container status"
	@echo "  $(GREEN)make clean$(NC)          - Remove containers and images"
	@echo "  $(GREEN)make fclean$(NC)         - Full cleanup including data"
	@echo "  $(GREEN)make re$(NC)             - Rebuild everything"
	@echo "  $(GREEN)make help$(NC)           - Show this help message"
	@echo "$(BLUE)========================================$(NC)"
