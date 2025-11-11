NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
RM          = rm -f

HEADER      = ./header.h

LIBFT_DIR   = ./includes/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_SRCS  = $(wildcard $(LIBFT_DIR)/*.c)

SRCS        = main.c parsing.c parsing_extras.c raycasting.c raycasting_extras.c
OBJ_SRCS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SRCS) $(LIBFT) -lm -o $(NAME)

$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ_SRCS)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

bc: all clean

.PHONY: all clean fclean re bc
