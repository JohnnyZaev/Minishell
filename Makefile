# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 16:28:21 by gvarys            #+#    #+#              #
#    Updated: 2022/02/16 15:17:29 by gvarys           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell

CC					=	gcc
CFLAGS				=	-O2 -Wall -Wextra -Werror

RM					=	rm -rf

SRC_DIR				=	src/

HEADER_DIR			=	includes/

LIBFT_DIR			=	libft/
LIBFT				=	$(LIBFT_DIR)/libft.a

READLINE_FLAGS		= -L/Users/gvarys/.brew/opt/readline/lib -I/Users/gvarys/.brew/opt/readline/include

HEADER				=	$(HEADER_DIR)minishell.h

SRC_FILES			=	main.c\
						utils/minishell_utils.c\
						utils/pipes_and_pids.c\
						utils/execute_and_redirects.c\
						utils/error.c\
						utils/ft_split_max.c\
						utils/clean.c\
						builtins/unset.c\
						builtins/env.c\
						builtins/exit.c\
						builtins/pwd.c\
						builtins/export.c\
						builtins/cd.c\
						builtins/echo.c\
						envs/envs.c\
						envs/envs_utils.c\
						signals/signals.c\
						parser/parser.c\
						parser/parser_utils.c

OBJS				=	$(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))

all					:	$(LIBFT) $(NAME)

$(LIBFT)			:
							make -C $(LIBFT_DIR)

$(NAME)				:	$(OBJS)
							$(CC) $(CFLAGS)  -lreadline $(READLINE_FLAGS) -L$(LIBFT_DIR) -lft $(OBJS) -o $@

%.o					:	%.c $(HEADER)
							$(CC) $(CFLAGS) -c $< -o $@

clean				:
							$(RM) $(OBJS)
							make -C $(LIBFT_DIR) clean

fclean				:	clean
							$(RM) $(NAME)
							make -C $(LIBFT_DIR) fclean

re					:	fclean all

.PHONY				:	all clean fclean re
