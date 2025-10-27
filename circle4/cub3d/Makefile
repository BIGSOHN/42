CC := cc
CFLAG := -Wall -Wextra -Werror -g
RM := rm -r
NAME := cub3D

# Directories
LIBFT_DIR := ./libft
INC_DIR := ./header_dir
MAIN_DIR := ./main_dir
PARSE_DIR := ./parse_dir
CHECK_FILE_DIR := ./check_file_dir
COMFORT_UTILS_DIR := ./comfort_utils_dir
CONFIG_DIR := ./config_dir
RENDER_DIR := ./render_dir
ERROR_DIR := ./error_dir
OBJ_DIR := obj_dir
MINILIBX_DIR = ./minilibx-linux

# Files
SRC_FILES_MAIN :=	main.c
SRC_FILES_PARSE :=	parse_data_utils.c \
					parse_fail_msg.c \
					parse_file_utils.c \
					parse_map_utils.c \
					parse_textures_utils.c \
					prepare.c
SRC_FILES_CHECK :=	check_color_utils.c \
					check_file_utils.c \
					check_map_utils.c
SRC_FILES_COMFORT :=	comfortable_utils.c \
						free_utils.c
SRC_FILES_CONFIG :=	init.c \
					setup.c \
					setup_utils.c \
					key_handler.c
SRC_FILES_RENDER :=	render.c \
					raycasting.c \
					raycasting_utils.c \
					draw_background.c \
					draw_wall.c \
					draw_utils.c
SRC_FILES_ERROR :=	error.c \
					destroy.c

# Include paths
INC_FLAGS := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)

# Source files
SRCS_MAIN := $(addprefix $(MAIN_DIR)/, $(SRC_FILES_MAIN))
SRCS_PARSE := $(addprefix $(PARSE_DIR)/, $(SRC_FILES_PARSE))
SRCS_CHECK := $(addprefix $(CHECK_FILE_DIR)/, $(SRC_FILES_CHECK))
SRCS_COMFORT := $(addprefix $(COMFORT_UTILS_DIR)/, $(SRC_FILES_COMFORT))
SRCS_CONFIG := $(addprefix $(CONFIG_DIR)/, $(SRC_FILES_CONFIG))
SRCS_RENDER := $(addprefix $(RENDER_DIR)/, $(SRC_FILES_RENDER))
SRCS_ERROR := $(addprefix $(ERROR_DIR)/, $(SRC_FILES_ERROR))
SRCS := $(SRCS_MAIN) \
		$(SRCS_PARSE) \
		$(SRCS_CHECK) \
		$(SRCS_COMFORT) \
		$(SRCS_CONFIG) \
		$(SRCS_RENDER) \
		$(SRCS_ERROR) \

# Object files
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) $(INC_FLAGS) -c $< -o $@

# Libft
LIBFT := $(LIBFT_DIR)/libft.a

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@echo -n "NOW_LOADING..."
	@make -C $(LIBFT_DIR) all --no-print-directory
	@make -C $(MINILIBX_DIR) all --no-print-directory
	@$(CC) $(CFLAG) $(OBJS) $(LIBFT) -L./minilibx-linux -lmlx_Linux -L/usr/lib -I./minilibx-linux -lXext -lX11 -lm -lz -o $@
	@echo "READY TO EVALUATE"

clean :
	@echo "NOW_EXECUTE_CLEANING"
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@if [ -e $(OBJ_DIR) ]; then \
		$(RM) -r $(OBJ_DIR); \
	fi
	@if [ -e $(MINILIBX_DIR) ]; then \
		make -C $(MINILIBX_DIR) clean --no-print-directory; \
	fi
	@echo "THE PROCESS END"

fclean :
	@echo "NOW_EXECUTE_FCLEANING"
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@if [ -e $(OBJ_DIR) ]; then \
		$(RM) -r $(OBJ_DIR); \
	fi
	@if [ -f $(NAME) ]; then \
		$(RM) $(NAME); \
	fi
	@if [ -e $(MINILIBX_DIR) ]; then \
		make -C $(MINILIBX_DIR) clean --no-print-directory; \
	fi
	@echo "THE PROCESS END"

re :
	@make fclean --no-print-directory
	@make all --no-print-directory
