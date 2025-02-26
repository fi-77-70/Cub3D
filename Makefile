# _______________________________________________________________
#|___________________________[VARIABLES]_________________________|
#|_______________________________________________________________|

CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror
NAME			= cub3d

INC				= -I./include
LIBFT			= libs/libft/libft.a

MLXFLAGS 		= -L minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11
MLX				= minilibx-linux/libmlx_Linux.a

GENERAL			= main.c

UTILS			= init.c get_content_utils.c formating_tools.c

PARSING			= get_elements.c parsing_utils.c ft_cub_split.c 

# _______________________________________________________________
#|___________________________[SRC FILES]_________________________|
#|_______________________________________________________________|

SRC				= $(GENERAL)\
					$(UTILS)\
					$(PARSING)

VPATH			= src\
					src/utils\
					src/parsing

OBJ_DIR			= obj

OBJ 			= $(SRC:%.c=$(OBJ_DIR)/%.o)

# _______________________________________________________________
#|_____________________________[RULES]___________________________|
#|_______________________________________________________________|

all:			$(NAME)

$(OBJ_DIR):
				mkdir -p obj

$(OBJ_DIR)/%.o: %.c
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME):		$(OBJ_DIR) $(OBJ) $(MLX) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):		libs/libft/*.c
				make -C libs/libft
				mv libs/libft/*.o obj/
				mv libs/libft/ft_printf/*.o obj/
				mv libs/libft/get_next_line/*.o obj/

$(MLX):
				make -C minilibx-linux

clean:
				$(RM) $(OBJ_DIR)

fclean: 		clean rmlx
				$(RM) $(NAME)
				$(RM) $(LIBFT)

re: 			fclean all

rmlx:
	rm -rf minilibx-linux

valgrind:
	valgrind --leak-check=full -s --show-leak-kinds=all ./$(NAME)

download:
	@wget https://cdn.intra.42.fr/document/document/25858/minilibx-linux.tgz
	@tar -xzf minilibx-linux.tgz
	@rm minilibx-linux.tgz

gdb:
	gdb --tui ./$(NAME)

.PHONY: 		all clean fclean re