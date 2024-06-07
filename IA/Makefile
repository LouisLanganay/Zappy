##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME	=	zappy_ai

SRC =	src/Client.py

all: $(NAME)

$(NAME):
	cp $(SRC) $(NAME)
	chmod +x $(NAME)

clean:
		rm -rf ./src/__pycache__

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re