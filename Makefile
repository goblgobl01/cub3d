NAME        = cub3D

HEADER      = ./header.h

LIBFT_DIR   = ./includes/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_SRCS  = $(wildcard $(LIBFT_DIR)/*.c)

SRC         = main.c parsing.c raycasting.c rendering.c parsing_extras.c raycasting_extras.c movement.c parsing_extras0.c parsing_extras1.c parsing_extras2.c RGBtoINT.c
OBJ         = $(SRC:.c=.o)

CFLAGS      = -Wall -Wextra -Werror -I. -IMLX42/include # -fsanitize=address -g
CC          = cc

MLX         = ./MLX42/build/libmlx42.a
LFLAGS      = -framework Cocoa -framework OpenGL -framework IOKit \
              -L ~/.brew/opt/glfw/lib/ -lglfw

RED         = \033[0;31m
GRN         = \033[0;32m
YEL         = \033[1;33m
RESET       = \033[0m

all: $(NAME)

# Build cub3D
$(NAME): $(OBJ) $(LIBFT) header.h
	@if find . -name "libmlx42.a" | grep -q .; then \
		echo "$(GRN)mlx found$(RESET)"; \
	else \
		echo "$(YEL)MLX42 not found, setting it up...$(RESET)"; \
		rm -rf MLX42; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
		cd MLX42 && cmake -B build && cmake --build build; \
	fi
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(LFLAGS) -o $(NAME)

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
