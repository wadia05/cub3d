NAME = cub3D
NAMEB = cub3D_Bonus
HDER = Mandatory/cub3d.h
HDERB = Bonus/cub3D_Bonus.h
SRC = \
	track_memory/memory_tracker.c \
	Mandatory/map_parsing_v2/main.c \
	Mandatory/map_parsing_v2/parsing.c \
	Mandatory/map_parsing_v2/color_parse.c\
	GET_NEXT_LINE_42/get_next_line.c \
	GET_NEXT_LINE_42/get_next_line_utils.c \
	Mandatory/map_parsing_v2/tools.c\
	Mandatory/map_parsing_v2/color_tools.c\
	Mandatory/map_parsing_v2/louding_maps.c\
	Mandatory/map_parsing_v2/map_parsing.c\
	Mandatory/map_parsing_v2/map_parsing_p2.c\
	Mandatory/map_parsing_v2/player_parse.c\
	Mandatory/map_parsing_v2/free_at_exit.c\
	Mandatory/map_parsing_v2/parsing_helper.c \
	Mandatory/map_parsing_v2/parsing_2.c \
	Mandatory/map_parsing_v2/map_parsing_door.c \
	Mandatory/animation_move.c\
	Mandatory/main.c \
	Mandatory/draw_rays_copy.c \
	Mandatory/texture.c \
	Mandatory/draw_rays_copy2.c \
	Mandatory/animation_kick.c \
	Mandatory/utils1.c \
	Mandatory/utils2.c \
	Mandatory/recasting.c \
	Mandatory/cal_wall.c \
	Mandatory/rander.c \
	Mandatory/main_v2.c

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
	Bonus/map_parsing_v2/parsing_helper.c \
	Bonus/map_parsing_v2/parsing_2.c \
	Bonus/map_parsing_v2/map_parsing_door.c \
	Bonus/animation_move.c\
	Bonus/main.c \
	Bonus/draw_rays_copy.c \
	Bonus/texture.c \
	Bonus/draw_rays_copy2.c \
	Bonus/animation_kick.c \
	Bonus/minimap_door.c \
	Bonus/utils1.c \
	Bonus/utils2.c \
	Bonus/recasting.c \
	Bonus/cal_wall.c \
	Bonus/rander.c \
	Bonus/main_v2.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)
MLX = "./MLX42/build/libmlx42.a"
LIBFT_DIR := ./libft_42
LIBFT := $(LIBFT_DIR)/libft.a

# # linux
# LDFLAGS = -Iinclude -ldl -lglfw -pthread -lm
# MAC
LDFLAGS = -O3 -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"
# LDFLAGS = -O3 -Iinclude -lglfw -L"opt/homebrew/opt/glfw/lib"
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(HDER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(LDFLAGS) $(FRAMEWORKS) -o $(NAME)

bonus: $(LIBFT) $(OBJB) $(HDERB)
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

# .PHONY: all clean fclean re bonus