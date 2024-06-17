##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME = zappy_ai
CLIENT_NAME = client

SRC = src/Main.py
CLIENT_SRC = src/Client.py

all: $(NAME) $(CLIENT_NAME)

$(NAME):
	ln -sf $(abspath $(SRC)) $(abspath $(NAME))

$(CLIENT_NAME):
	ln -sf $(abspath $(CLIENT_SRC)) $(abspath $(CLIENT_NAME))
	chmod +x $(abspath $(CLIENT_SRC))

clean:
	rm -rf src/__pycache__

fclean: clean
	rm -f $(NAME) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re
