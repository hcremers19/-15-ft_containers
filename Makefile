# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 14:08:18 by hcremers          #+#    #+#              #
#    Updated: 2022/12/25 12:19:51 by hcremers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= $(NAME1) $(NAME2)
NAME1			= ft_containers
NAME2			= std_containers

SRC1			= ft_main.cpp \
				Tests/ft_map.cpp \
				Tests/ft_stack.cpp \
				Tests/ft_vector.cpp \

SRC2			= std_main.cpp \
				Tests/std_map.cpp \
				Tests/std_stack.cpp \
				Tests/std_vector.cpp \

OBJ				= $(OBJ1) $(OBJ2)
OBJ1			= $(SRC1:.cpp=.o)
OBJ2			= $(SRC2:.cpp=.o)

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
				$(RM) $(wildcard *.o) $(wildcard */*.o)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re