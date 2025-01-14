NAME = cub3d
NAMEB = cub3d_Bonus
HDER = mandatory/cub3d.h
HDERB = Bonus/cub3d.h
SRC = \
	track_memory/memory_tracker.c \
	mandatory/map_parsing_v2/main.c \
	mandatory/map_parsing_v2/parsing.c \
	mandatory/map_parsing_v2/color_parse.c\
	GET_NEXT_LINE_42/get_next_line.c \
	GET_NEXT_LINE_42/get_next_line_utils.c \
	mandatory/map_parsing_v2/tools.c\
	mandatory/map_parsing_v2/color_tools.c\
	mandatory/map_parsing_v2/louding_maps.c\
	mandatory/map_parsing_v2/map_parsing.c\
	mandatory/map_parsing_v2/map_parsing_p2.c\
	mandatory/map_parsing_v2/player_parse.c\
	mandatory/map_parsing_v2/free_at_exit.c\
	mandatory/main.c \
	mandatory/draw_rays_copy.c \
	mandatory/texture.c \
	mandatory/draw_rays_copy2.c

SRCB = \
	track_memory/memory_tracker.c \
	Bonus/map_parsing_v2/main.c \
	Bonus/map_parsing_v2/parsing.c \
	Bonus/map_parsing_v2/color_parse.c\
	GET_NEXT_LINE_42/get_next_line.c \
	GET_NEXT_LINE_42/get_next_line_utils.c \
	Bonus/map_parsing_v2/tools.c\
	Bonus/map_parsing_v2/color_tools.c\
	Bonus/map_parsing_v2/louding_maps.c\
	Bonus/map_parsing_v2/map_parsing.c\
	Bonus/map_parsing_v2/map_parsing_p2.c\
	Bonus/map_parsing_v2/player_parse.c\
	Bonus/map_parsing_v2/free_at_exit.c\
	Bonus/main.c \
	Bonus/draw_rays_copy.c \
	Bonus/texture.c \
	Bonus/draw_rays_copy2.c

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
AR = ar rcs
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)
MLX = "./MLX42/build/libmlx42.a"
LIBFT_DIR := ./libft_42
LIBFT := $(LIBFT_DIR)/libft.a

# linux
# LDFLAGS = -Iinclude -ldl -lglfw -pthread -lm
#MAC
LDFLAGS = -O3 -Iinclude -lglfw -L"/Users/wait-bab/.brew/opt/glfw/lib"
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(HDER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(LDFLAGS) $(FRAMEWORKS) -o $(NAME)

bonus: fclean $(LIBFT) $(OBJB) $(HDERB)
	$(CC) $(CFLAGS) $(OBJB) $(MLX) $(LIBFT) $(LDFLAGS) $(FRAMEWORKS) -o $(NAMEB)

%.o: %.c $(HDER) $(HDERB)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ) $(OBJB)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAMEB)

re: fclean all

.PHONY: all clean fclean re bonus