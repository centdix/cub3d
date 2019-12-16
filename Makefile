DIR_S = srcs

DIR_O = objs

MLX_DIR = minilibx

LIBFT_DIR = libft

SOURCES = get_next_line.c \
			get_next_line_utils.c \
			get_param.c \
			get_param_utils.c \
			check_file.c \
			get_map.c \
			handle_map.c \
			has_error.c \
			render.c \
			draw.c \
			draw_sprites.c \
			draw_sprites_utils.c \
			draw_weapon.c \
			hook.c \
			move.c \
			rotate.c \
			ft_shoot.c \
			create_bmp.c \
			create_bmp_utils.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

NAME = Cub3D

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBS = -framework OpenGL -framework AppKit

MLX_LIB	= $(addprefix $(MLX_DIR)/,libmlx.a)

LIBFT = $(addprefix $(LIBFT_DIR)/,libft.a)

all: $(LIBFT) $(MLX) $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(LIBS) $^ main.c -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: clean all fclean re
