# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/29 19:25:16 by dimachad          #+#    #+#              #
#    Updated: 2025/09/29 20:06:35 by dimachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS 	= cc -Wall -Werror -Wextra
HEADER	= philo.h
DEBUGFLAGS  = -g3 -fsanitize=address

SRC		= main.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CFLAGS) -c $< -o $@

debug: fclean
	$(CFLAGS) $(DEBUGFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

