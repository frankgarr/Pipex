# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/17 09:04:06 by frankgar          #+#    #+#              #
#    Updated: 2024/03/22 10:02:24 by frankgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread -fsanitize=address 
INCLUDES = -I ./inc/\
           -I ./libft/
SRC = main.c parsing.c

DIR_SRC = ./src
DIR_OBJ = $(DIR_SRC)/obj
OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.d))


all: dir $(NAME)

-include $(DEP)
dir:
	make -C ./libft/ --no-print-directory 
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c Makefile
	$(CC) -MMD $(FLAGS)  -c $< -o $@ $(INCLUDES)
$(NAME): $(OBJ) ./libft/libft.a
	$(CC) $(FLAGS) $(OBJ) ./libft/libft.a -o $@ $(INCLUDES)
	echo "$(NAME) Created :D"
clean:
	rm -rf $(DIR_OBJ)
	make clean -C ./libft/ --no-print-directory 
	echo "DEPENDENCIES Erased :D"
fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/ --no-print-directory 
	echo "EVERYTHING Erased D:"
re: fclean all
.PHONY: fclean all clean re dir
.SILENT:
