# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmartina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 16:01:11 by qmartina          #+#    #+#              #
#    Updated: 2019/10/17 16:01:15 by qmartina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	21sh

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
D_FLAGS		=	-g

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)libft.h

LIBS		=	-ltermcap

SRC_DIR		=	src/
INC_DIR		=	inc/
OBJ_DIR		=	objs/

SRC_BASE = builtins/ft_cd.c\
        builtins/ft_echo.c\
        builtins/ft_echo2.c\
        builtins/allenv/ft_env.c\
        errors/errror_handler.c\
        exec/ft_create_file.c\
        exec/ft_do_pipe.c\
        exec/ft_fun_fork.c\
	lexer/lexer.c\
	lexer/change_dol.c\
	lexer/change_spaces.c\
	lexer/cr_and_add_tokens.c\
	lexer/dop_funs.c\
	lexer/kill_dop_structure.c\
	lexer/word_sizes.c\
	lexer/change_hist_exp.c\
	lexer/change_str_by_str.c\
	lexer/do_subshell.c\
	lexer/get_opt_type.c\
	nucleus/ft_cutcopy.c\
	nucleus/ft_read_8.c\
	nucleus/nucleus.c\
	nucleus/nucleus2.c\
	nucleus/nucleus3.c\
	nucleus/nucleus4.c\
        parser/dop_parser.c\
        parser/change_tilda.c\
        parser/main_parser.c\
	ft_distruct.c\
	ft_error_q.c\
	ft_signal.c\
	ft_take_arg.c\
	main.c\
	builtins/allenv/main_env.c\
	builtins/alias/ft_alias.c\
	evaln/ft_do_zam_eval.c\
	evaln/atoimy.c\
	evaln/inftopost.c\
	evaln/calc.c\
	evaln/dop.c\


SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all :
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

$(NAME):		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) \
		$(LIBFT_LIB) \
		$(FLAGS) $(D_FLAGS)
	@strip -x $@
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $(NAME)\033[0m\033[K\n"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*.*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) $(DELTA) "$@"
	@$(CC) $(FLAGS) $(D_FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:			cleanlib
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖ clean $(NAME).\033[0m\033[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME).\033[0m\033[K\n"

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all

relib:			fcleanlib $(LIBFT_LIB)

.PHONY :		fclean clean re relib cleanlib fcleanlib

-include $(OBJS:.o=.d)