# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 23:27:47 by pchambon          #+#    #+#              #
#    Updated: 2019/10/08 17:03:37 by pchambon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

DIRSRCS = ./srcs/

DIROBJ = ./obj/

SRCS = main.c \
		parser.c \
		init.c \
		init_tex.c \
		window.c \
		raycaster.c \
		key_func.c \
		texture.c \
		floor.c \

INC = ./includes/wolf3d.h

LIB = ./X-Libft/

LIB_H = ./X-Libft/libft.h

LIB_A = ./X-Libft/libft.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

OBJ = $(patsubst %.c,$(DIROBJ)%.o,$(SRCS))

FRAMEWORK = -lmlx -framework OpenGL -framework Appkit

NO_COLOR    = \x1b[0m
OK_COLOR    = \x1b[32;01m
WARN_COLOR  = \x1b[33;01m
ERROR_COLOR = \x1b[31;01m
_BLACK = \033[30m
_RED = \033[31m
_GREEN = \033[32m
_YELLOW = \033[33m
_BLUE = \033[34m
_PURPLE = \033[35m
_CYAN = \033[36m
_GREY = \033[37m

verif = 0

all:			$(NAME)

$(LIB_A):
				@make -C $(LIB)

$(NAME):		$(LIB_A) $(OBJ)
				@$(CC) $^ -I $(INC) -I $(LIB_H) $(CFLAGS) $(FRAMEWORK) $(LIB_A) -o $@
				@echo "\n\n${OK_COLOR}Wolf3d : Compilation complete${NO_COLOR}"

$(DIROBJ)%.o:	$(DIRSRCS)%.c $(INC)
				@mkdir -p $(DIROBJ)
				@if [[ $(verif) -eq 0 ]]; then printf "\n$(_BLUE)|==========================>  $(_PURPLE)$(NAME)   $(_BLUE)<==========================|$(_DEF)\n";\
				else printf "\e[1A"; fi
				$(eval FNCT = $(words $(SRCS)))
				$(eval verif = $(shell echo $(verif) + 1 | bc ))
				$(eval PCR = $(shell echo "$(verif) / $(FNCT) * 100" | bc -l))
				@printf " \n$(_GREEN)[%3d%%]$(_RED)\t$(_DEF)%-24s 👉$(_YELLOW)\t%-24s$(_DEF)" $(shell echo $(PCR) | sed -E "s:\.[0-9]{20}::") $< $@
				@$(CC) $(CFLAGS) -o $@ -c $<

clean:
				@make -C $(LIB) clean
				@rm -f $(OBJ)
				@echo "${OK_COLOR}Wolf3d : Object files deleted${NO_COLOR}"

fclean:
				@make -C $(LIB) fclean
				@rm -f $(OBJ)
				@rm -rf $(DIROBJ)
				@echo "${WARN_COLOR}Wolf3d : Object files deleted${NO_COLOR}"
				@rm -f $(NAME)
				@echo "${OK_COLOR}Wolf3d : Executable deleted${NO_COLOR}"

re:				fclean all

.PHONY:			all clean fclean re
