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

NAME	= 21sh

SRC = 	src/builtins/ft_cd.c\
        src/builtins/ft_echo.c\
        src/builtins/ft_echo2.c\
        src/builtins/allenv/ft_env.c\
        src/errors/errror_handler.c\
        src/exec/ft_create_file.c\
        src/exec/ft_do_pipe.c\
        src/exec/ft_fun_fork.c\
	src/lexer/lexer.c\
	src/lexer/change_dol.c\
	src/lexer/change_spaces.c\
	src/lexer/cr_and_add_tokens.c\
	src/lexer/dop_funs.c\
	src/lexer/kill_dop_structure.c\
	src/lexer/word_sizes.c\
	src/lexer/change_hist_exp.c\
	src/lexer/change_str_by_str.c\
	src/lexer/do_subshell.c\
	src/lexer/get_opt_type.c\
	src/nucleus/ft_cutcopy.c\
	src/nucleus/ft_read_8.c\
	src/nucleus/nucleus.c\
	src/nucleus/nucleus2.c\
	src/nucleus/nucleus3.c\
	src/nucleus/nucleus4.c\
        src/parser/dop_parser.c\
        src/parser/dop_parser1.c\
        src/parser/main_parser.c\
	src/ft_distruct.c\
	src/ft_error_q.c\
	src/ft_signal.c\
	src/ft_take_arg.c\
	src/main.c\
	src/builtins/allenv/main_env.c\
	src/builtins/alias/ft_alias.c\
	src/evaln/ft_do_zam_eval.c\
	src/evaln/atoimy.c\
	src/evaln/inftopost.c\
	src/evaln/calc.c\
	src/evaln/dop.c\


OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(OBJ) -I inc -o $(NAME) -L libft/ -lft -ltermcap
	@echo "\033[32m21sh: Built.\033[0m"

%.o:%.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(OBJ)
	@echo "\033[32m21sh: Cleaned up object files.\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME) $(OBJ)
	@echo "\033[32m21sh: Cleaned up compiled files.\033[0m"

re: fclean $(NAME)
