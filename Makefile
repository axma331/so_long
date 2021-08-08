NAME		= so_long

CC			:= gcc
RM			:= rm -rf
CFLAGS		:= -Wall -Wextra -Werror -O2 #-g -fsanitize=address

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LIBFT_GIT		:= https://github.com/axma331/libft.git

HEADER			:= $(NAME).h

MLX_DIR			= mlx
MLXLIB			= $(MLX_DIR)/libmlx.dylib
MLXFLAGS		= $(MLXLIB) -lmlx -framework OpenGL -framework AppKit

# SRCS			:= $(wildcard *.c)
SRCS			:= so_long_create_game.c so_long_draw.c so_long_init.c so_long_utils.c so_long.c

OBJ_DIR			:= .obj
OBJC			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all:  			libft_make $(NAME)

$(NAME): 		$(OBJC) $(MLXLIB) Makefile
				@$(CC) $(LIBFT) -I $(MLXFLAGS) $(OBJC) -o $@
				@echo "$(CLRCY)Создан$(CLREL)$@$(CLRRS)"

$(OBJ_DIR)/%.o:	%.c $(HEADER) $(LIBFT) | $(OBJ_DIR)
				$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@
				@echo "$(CLRCY)Создан$(CLRGR)$@$(CLRRS)"

$(OBJ_DIR):
				mkdir -p $@

$(MLXLIB):
				make -sC $(MLX_DIR)
				@echo "$(CLRCY)Подключен$(CLRPR)$(MLXLIB)$(CLRRS)"

$(LIBFT):
				make -C $(LIBFT_DIR)
				@echo "$(CLRCY)Подключен$(CLRPR)$(LIBFT)$(CLRRS)"

bonus:			all

re:
				make fclean
				make all

clean:
				-make clean -C $(LIBFT_DIR)
				make clean -C mlx
				$(RM) $(OBJ_DIR)
				@echo "$(CLRCY)Очистка$(CLRRE)$(OBJ_DIR)$(CLRRS)"

fclean: clean
				-make fclean -C $(LIBFT_DIR)
				$(RM) $(NAME)
				$(RM) $(LIBFT_DIR)
				@echo "$(CLRCY)Удаление$(CLRRE)$(NAME) $(CLRRS)"

libft_make:
				@make -C $(LIBFT_DIR) || { git clone $(LIBFT_GIT); make -C $(LIBFT_DIR); }

gitpush: fclean
				git status
				git add .
				git commit -m "New edition"
				git push

.PHONY: 		all re clean fclean libft_make




#-c говорит не запускать линкер, потому что нет main
#-g порождает отладочную информацию в родном формате операционной системы
#включает использование дополнительной отладочной информации, 
#которую может использовать только GDB; 
#эта дополнительная отладочная информация делает работу отладки в GDB лучше, но может, 
#вероятно испортить работу других отладчиков, или помешать им прочитать программу.

CLRRS = \033[0m #сброс цвета
BOLDf = \033[1m #жирный шрифт
UNDRL = \033[4m #подчеркивание
FONGR = \033[47m #серый цвет фона
CLRGR = \033[37m #серый цвет шрифта
FONCY = \033[46m #цвет морской волны фона		
CLRCY = \033[36m #цвет морской волны шрифта
FONPR = \033[45m #фиолетовый цвет фона
CLRPR = \033[35m #фиолетовый цвет шрифта
FONBL = \033[44m #синий цвет фона
CLRBL = \033[34m #синий цвет шрифта
FONEL = \033[43m #желтый цвет фона
CLREL = \033[33m #желтый цвет шрифта
FONGR = \033[42m #зелёный цвет фона
CLRGR = \033[32m #зелёный цвет шрифта
FONRE = \033[41m #красный цвет фона
CLRRE = \033[31m #красный цвет шрифта
FONBC = \033[40m #чёрный цвет фона
CLRBC = \033[30m #чёрный цвет шрифта
#COLOR+FON = \033[6;35m - можно совмещать \033[6 - цвет шрифта ;35m - цвет фона