# NAME		= cub3d

# CC			= cc
# CFLAGS		= -Wall -Wextra -Werror

# RM			= rm -f
# HEADER		= ./header.h
# LIBFT		= ./includes/libft/libft.a

# SRCS		= main.c 

# OBJ_SRCS	= $(SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJ_SRCS) $(LIBFT) $(HEADER)
# 	$(CC) $(CFLAGS) $(OBJ_SRCS) $(LIBFT) -o $(NAME)

# %.o: %.c $(HEADER)
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(LIBFT):
# 	@$(MAKE) -C ./includes/libft

# clean:
# 	@$(MAKE) clean -C ./includes/libft
# 	@$(RM) $(OBJ_SRCS)

# fclean: clean
# 	@$(RM) $(LIBFT)
# 	$(RM) $(NAME)

# re: fclean all

# bc: all clean

# .PHONY: all clean fclean re bc

# ===============================
#      cub3d Makefile (with libft)
# ===============================

NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror 
RM          = rm -f

HEADER      = ./header.h

# --- libft setup ---
LIBFT_DIR   = ./includes/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_SRCS  = $(wildcard $(LIBFT_DIR)/*.c)

# --- source files for cub3d ---
SRCS        = main.c parsing.c parsing_extras.c raycasting.c raycasting_extras.c
OBJ_SRCS    = $(SRCS:.c=.o)

# ===============================
#          BUILD RULES
# ===============================

all: $(NAME)

$(NAME): $(OBJ_SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SRCS) $(LIBFT) -o $(NAME)

$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
#          CLEAN RULES
# ===============================

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ_SRCS)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

bc: all clean

.PHONY: all clean fclean re bc
