##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME = zappy_ai
CLIENT_NAME = client

SRC = src/Main.py

all: $(NAME)

$(NAME):
	ln -sf $(abspath $(SRC)) $(abspath $(NAME))

clean:
	rm -rf src/__pycache__

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
