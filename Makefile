# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 16:28:21 by gvarys            #+#    #+#              #
#    Updated: 2022/02/08 14:49:02 by gvarys           ###   ########.fr        #
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

HEADER				=	$(HEADER_DIR)minishell.h

SRC_FILES			=	main.c\
						utils/minishell_utils.c\
						utils/pipes_and_pids.c\
						envs/envs.c\
					

OBJS				=	$(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))

all					:	$(LIBFT) $(NAME)

$(LIBFT)			:
							make -C $(LIBFT_DIR)

$(NAME)				:	$(OBJS)
							$(CC) $(CFLAGS)  -lreadline -L$(LIBFT_DIR) -lft $(OBJS) -o $@

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