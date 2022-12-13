# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcremers <hcremers@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 14:08:18 by hcremers          #+#    #+#              #
#    Updated: 2022/12/13 16:39:41 by hcremers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= test

SRC				= main.cpp

OBJ				= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))
OBJDIR			= Objects/

CC				= c++
CFLAGS			= -Wall -Wextra -Werror -std=c++98 -g

RM				= rm -rf
MKDIR			= mkdir

# ---------- #

$(OBJDIR)%.o:	%.cpp
				$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJDIR), $(<:.cpp=.o))

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ):			| $(OBJDIR)

$(OBJDIR):
				$(MKDIR) $(OBJDIR)

clean:
				$(RM) $(OBJDIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re