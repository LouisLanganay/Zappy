##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -I.
LIBS = -L../lib/protocol -lmyprotocol

SRCS = main.c test_server.c
OBJS = $(SRCS:.c=.o)

TARGET = test_server

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: clean
