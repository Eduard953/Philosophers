# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebeiline <ebeiline@42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 16:15:03 by ebeiline          #+#    #+#              #
#    Updated: 2022/03/29 17:11:02 by ebeiline         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -pthread -g -fsanitize=thread

NAME		= philosophers

MAKE		= make

SRC			= main.c philosophers.c init.c time.c utils.c clean.c

OBJ			= ${SRC:.c=.o}


all:		$(NAME)


$(NAME): $(SRC)
		$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(INCLUDES)

clean:		
		$(RM) $(OBJ)

fclean:		clean
			/bin/rm -f $(NAME)

re:			fclean all
