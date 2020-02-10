NAME = cub3D

# include mk/colors.mk

SRC = cub3d.c \
		init.c \
		raycast.c \
		load_texture.c \
		wall_hit.c \
		draw_text.c \
		check.c \
		error.c \
		deal_key.c \
		sprite.c \
		orientation.c \
		fill_map.c \
		save.c \
		game.c \
		guess.c \

OBJ=$(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) | makelib
	@$(CC) -I. $(OBJ) -L libft -lft -lmlx -framework OpenGL -framework AppKit -lm -o $(NAME)

makelib:
	@$(MAKE) -C libft

%.o: %.c
	@echo "$(BOLD)$(BLUE)cub$(patsubst obj/%, %, $(basename $@))$(GREEN)[OK]$(END)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(INC_PATH) -o $@ -c $<

clean:
	$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Library deleted$(END)"
	@echo "$(RED)object files deleted$(END)"

re: fclean all

.PHONY: all clean fclean re makelib