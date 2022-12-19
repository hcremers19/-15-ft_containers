# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 14:08:18 by hcremers          #+#    #+#              #
#    Updated: 2022/12/19 16:25:24 by hcremers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= $(NAME1) $(NAME2)
NAME1			= ft_containers
NAME2			= std_containers

SRC1			= Tests/ft_map.cpp
SRC2			= Tests/std_map.cpp

OBJ				= $(OBJ1) $(OBJ2)
OBJ1			= $(SRC1:.c=.o)
OBJ2			= $(SRC2:.c=.o)

CC				= c++
CFLAGS			= -Wall -Wextra -Werror -std=c++98 -g

RM				= rm -rf
MKDIR			= mkdir

# ---------- #

.cpp.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ1) -o $(NAME1)
				$(CC) $(CFLAGS) $(OBJ2) -o $(NAME2)

clean:
				$(RM) $(wildcard *.o)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re