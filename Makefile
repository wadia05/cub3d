NAME = cub3d
HDER = mandatory/cub3d.h
SRC = mandatory/main.c mandatory/draw_rays.c \
	track_memory/memory_tracker.c \
	map_parsing_v2/parsing.c \
	map_parsing_v2/color_parse.c\
	GET_NEXT_LINE_42/get_next_line.c \
	GET_NEXT_LINE_42/get_next_line_utils.c \
	map_parsing_v2/tools.c\
	map_parsing_v2/color_tools.c\
	map_parsing_v2/louding_maps.c\
	map_parsing_v2/map_parsing.c\
	map_parsing_v2/player_parse.c\
	map_parsing_v2/free_at_exit.c\

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
AR = ar rcs
OBJ = $(SRC:.c=.o)
MLX = "./includes/MLX42/libmlx42.a"
LIBFT_DIR := ./libft_42
LIBFT := $(LIBFT_DIR)/libft.a

LDFLAGS = -O3 -Iinclude  -lglfw -L"/Users/abenchel/.brew/opt/glfw/lib"
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(HDER) 
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LDFLAGS) $(LIBFT) $(FRAMEWORKS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re