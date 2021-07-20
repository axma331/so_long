NAME	= so_long

CC		= gcc
RM		= rm -rf
ERFLG	= #-g -fsanitize=address
CFLAGS	= $(ERFLG) #-Wall -Wextra -Werror
LIBFT	:= -L ../libft -lft
HEDER	:= *.h


MLXLIB		= mlx/libmlx.dylib
MLXFLAGS	= $(MLXLIB) -lmlx -framework OpenGL -framework AppKit

S_SRC	:= $(wildcard *.c)

OBJDIR	:= .obj
S_OBJ	:= $(S_SRC:%.c=$(OBJDIR)/%.o)

DEPDIR	:= .dep
DEPFILES := $(wildcard %.c=$(DEPDIR)/%.d)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

all: $(NAME)

$(NAME): $(S_OBJ) $(MLXLIB)
	@$(CC) $(LIBFT) -I $(MLXFLAGS) $(S_OBJ) -o $@
	@echo "$(CLRCY)Подключен$(CLRPR)$(LIBFT)$(CLRRS)"
	@echo "$(CLRCY)Подключен$(CLRPR)$(MLXLIB)$(CLRRS)"
	@echo "$(CLRCY)Создан$(CLREL)$@$(CLRRS)"

$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR) $(HEDER)
	@$(MAKE) -C ../libft
	@$(MAKE) -C ./mlx
	@$(CC) $(CFLAGS) $(DEPFLAGS) -I $(MLXLIB) -c $< -o $@
	@echo "$(CLRCY)Создан$(CLRGR)$@$(CLRRS)"

$(OBJDIR) $(DEPDIR):
	@mkdir -p $@

$(DEPFILES):
sinclude $(wildcard $(DEPFILES))

re:
	@$(MAKE) fclean
	@$(MAKE) all

clean:
	@$(MAKE) clean -C ../libft
	@$(MAKE) clean -C ./mlx
	@$(RM) $(OBJDIR) $(DEPDIR)
	@echo "$(CLRCY)Очистка$(CLRRE)$(OBJDIR)$(DEPDIR)$(CLRRS)"

fclean: clean
	@$(MAKE) fclean -C ../libft
	@$(RM) $(NAME)
	@echo "$(CLRCY)Удаление$(CLRRE)$(NAME) $(CLRRS)"

gitpush: fclean
	git status
	git add .
	git commit -m "New edition"
	git push

.PHONY: all clean fclean re




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