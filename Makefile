NAME = cub3d
HDER = mandatory/cub3d.h
SRC = \
	track_memory/memory_tracker.c \
	map_parsing/parsing.c \
	GET_NEXT_LINE_42/get_next_line.c \
	GET_NEXT_LINE_42/get_next_line_utils.c \
	map_parsing/map_parsing.c \
	map_parsing/player_parse.c
	# mandatory/main.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
OBJ = $(SRC:.c=.o)
MLX = "./MLX42/build/libmlx42.a"
LIBFT_DIR := ./libft_42
LIBFT := $(LIBFT_DIR)/libft.a

# linux
# LDFLAGS = -Iinclude -ldl -lglfw -pthread -lm
#MAC
LDFLAGS = -O3 -Iinclude -lglfw -L"/Users/wait-bab/.brew/Cellar/glfw/3.4/lib"
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(HDER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(LDFLAGS) $(FRAMEWORKS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re