# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtessier <jtessier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 14:34:58 by jtessier          #+#    #+#              #
#    Updated: 2022/09/16 11:27:26 by jtessier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo
CC			= gcc
FLAGS		= -Wall -Werror -Wextra -fsanitize=address -g

SRCS		=	main.c \
				./sources/parsing_1.c \
				./sources/parsing_2.c \
				./sources/launch.c \
				./sources/threads_do.c \
				./sources/div.c \
				./sources/initialize.c \
				./sources/philo_states.c \

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME): 	$(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)
	
fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
