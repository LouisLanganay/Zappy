##
## EPITECH PROJECT, 2024
## bs-rt
## File description:
## Makefile
##

include Makefile_colors.mk

NAME 		= zappy_gui
CC 			= g++

VPATH 		:= ./Source
VPATH 		+= ./Source/Core
VPATH 		+= ./Source/API
VPATH 		+= ./Source/Map
VPATH 		+= ./Source/Map/Player
VPATH 		+= ./Source/Map/Resources
VPATH 		+= ./Source/Map/Resources/Food
VPATH 		+= ./Source/Map/Resources/Linemate
VPATH 		+= ./Source/Map/Resources/Deraumere
VPATH 		+= ./Source/Map/Resources/Sibur
VPATH 		+= ./Source/Map/Resources/Mendiane
VPATH 		+= ./Source/Map/Resources/Phiras
VPATH 		+= ./Source/Map/Resources/Thystame
VPATH 		+= ./Source/Map/Tile
VPATH 		+= ./Source/Map/Team
VPATH 		+= ./Source/Map/Egg

vpath %.cpp $(VPATH)

SRC 		:= Main.cpp
SRC 		+= Core.cpp
SRC 		+= Api.cpp
SRC 		+= Map.cpp
SRC 		+= Player.cpp
SRC 		+= AResources.cpp
SRC 		+= Food.cpp
SRC 		+= Linemate.cpp
SRC 		+= Deraumere.cpp
SRC 		+= Sibur.cpp
SRC 		+= Mendiane.cpp
SRC 		+= Phiras.cpp
SRC 		+= Thystame.cpp
SRC 		+= Tile.cpp
SRC 		+= Team.cpp
SRC 		+= Egg.cpp

BUILD_DIR 	= build
OBJ 		:= $(SRC:%.c=$(BUILD_DIR)/%.o)

VPATH_DIRS  := $(sort $(dir $(wildcard $(addsuffix /, $(VPATH)))))
CFLAGS      += $(foreach dir, $(VPATH_DIRS), -iquote$(dir))
CFLAGS      +=-L/usr/local/lib -L/usr/lib -lraylib
CFLAGS      += -iquote../../libs/protocol/include -g -DDEBUG_MODE
LDFLAGS	 	:= -L../libs/ -lmyprotocol

BUILD_DIR   = build
OBJ         := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

DIE         = exit 1
ECHO        = echo -e

%.cpp:
	@ $(ECHO) "${_B_RED}[ERROR]${_END} File ${_B_WHITE}$@${_END} not found."
	@ $(DIE)

all: $(NAME)
	@ $(ECHO) "${_B_GREEN}[SUCCES]${_END} project compiled successfully !"

$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -c $< -o $@
	@ $(ECHO) "${_CYAN}[OK]$(_END) -> $(CC)    $(_U_WHITE)$<$(_END)"

$(NAME): $(OBJ)
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)
	@ $(ECHO) "${_CYAN}[OK]$(_END) -> $(CC)    \
	$(_U_WHITE)$(NAME) $(CFLAGS) ${_END}"
	@ $(ECHO) "$(_B_PURPLE)[STATS]$(_END) -> \
	$(_U_WHITE)$(shell echo "$?" | wc -w) file(s) compiled${_END}."

debug: CFLAGS += -g -DDEBUG_MODE
debug: clean all

clean:
	@ $(RM) *.gcda
	@ $(RM) *.gcno
	@ $(RM) *.gcov
	@ $(RM) vgcore.*
	@ $(RM) coding-style-reports.log
	@ $(RM)	$(OBJ)
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    *.gcda${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    *.gcno${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    *.gcov${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    vgcore.*${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    coding-style-reports.log${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(OBJ)${_END}"

fclean: clean
	@ $(RM) -r $(BUILD_DIR)
	@ $(RM)	$(NAME)
	@ $(RM)	$(NAME)_tests
	@ $(RM) -r doc
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(BUILD_DIR)${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(NAME)${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    $(NAME)_tests${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)    doc${_END}"

re: fclean all

.PHONY: all clean fclean re debug
