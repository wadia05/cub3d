NAME = cub3d
HDER = mandatory/cub3d.h
SRC = \
	track_memory/memory_tracker.c \
	map_parsing_v2/main.c \
	map_parsing_v2/parsing.c \
	map_parsing_v2/color_parse.c\
	GET_NEXT_LINE_42/get_next_line.c \
	GET_NEXT_LINE_42/get_next_line_utils.c \
	map_parsing_v2/tools.c\
	map_parsing_v2/color_tools.c\
	map_parsing_v2/louding_maps.c\
	map_parsing_v2/map_parsing.c\
	map_parsing_v2/map_parsing_p2.c\
	map_parsing_v2/player_parse.c\
	map_parsing_v2/free_at_exit.c\
	mandatory/main.c \
	mandatory/draw_rays.c \
	mandatory/texture.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
AR = ar rcs
OBJ = $(SRC:.c=.o)
MLX = "./MLX42/build/libmlx42.a"
LIBFT_DIR := ./libft_42
LIBFT := $(LIBFT_DIR)/libft.a

# linux
LDFLAGS = -Iinclude -ldl -lglfw -pthread -lm
#MAC
	# LDFLAGS = -O3 -Iinclude -lglfw -L"/Users/wait-bab/.brew/Cellar/glfw/3.4/lib"
	# FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

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