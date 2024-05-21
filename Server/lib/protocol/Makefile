##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

NAME		:=	libmyprotocol.a
EXT			:=	.c

DIR			:=	src/client
SRC			:=	$(addprefix $(DIR)/,								\
					create.c										\
					close.c											\
					listen.c										\
					send_packet.c									\
				)

DIR			+=	src/server
SRC			+=	$(addprefix $(lastword $(DIR))/,					\
					create.c										\
					close.c											\
					listen.c										\
					send_packet.c									\
				)

TEST_DIR	:=	tests
TEST_SRC	:=	$(addprefix $(TEST_DIR)/,							\
					client.c										\
					server.c										\
				)

DIR_BUILD	:=	build
DIR_BIN		:=	$(DIR_BUILD)/bin

DIR_OBJ		:=	$(DIR_BUILD)/obj
OBJ			:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(SRC))
DEP			:=	$(OBJ:.o=.d)

TEST_OBJ	:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(TEST_SRC))
TEST_DEP	:=	$(TEST_OBJ:.o=.d)

DG_DIR_OBJ	:=	$(DIR_BUILD)/debug
DG_OBJ		:=	$(patsubst %$(EXT),$(DG_DIR_OBJ)/%.o,$(SRC))
DG_DEP		:=	$(DG_OBJ:.o=.d)

DEBUG		:=	$(DIR_BIN)/debug

RM			:=	rm -rf

CC			:=	gcc
CFLAGS		:=	-iquote./include -iquote../../include				\
				-Wall -Wextra -fPIC -g
LDFLAGS		:=
CLINKER		:=	ar rc

all:				$(NAME)

define CREATE_DIR
	@if [ ! -d $(dir $@) ]; then									\
		mkdir -p $(dir $@) 											\
		&& printf "\033[93m[CREATED]\033[0m %s\n" $(dir $@)			\
		|| printf "\033[31m[ERROR]\033[0m %s\n"   $(dir $@);		\
	fi
endef

define BUILD_OBJ
	@$(RM) $(patsubst %.o,%.gcda,$@)
	@$(RM) $(patsubst %.o,%.gcno,$@)
	$(CREATE_DIR)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@								\
	&& printf "\033[32m[OK]\033[0m %s\n" $<							\
	|| printf "\033[31m[KO]\033[0m %s\n" $<
endef

$(DIR_OBJ)/%.o:		%$(EXT); $(BUILD_OBJ)
$(DG_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)

define COMPILE
	$(CREATE_DIR)
	@$(CC) -o $@ $^ $(LDFLAGS)			 							\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@						\
	|| printf "\033[31m[ERROR]\033[0m %s\n"  $@
endef

define COMPILE_LIB
	$(CREATE_DIR)
	@$(CLINKER) -o $@ $^											\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@						\
	|| printf "\033[31m[ERROR]\033[0m %s\n"  $@
endef

-include $(DEP)
$(NAME):			$(OBJ); 	$(COMPILE_LIB)

-include $(TEST_DEP)
client:				$(firstword $(TEST_OBJ));	$(COMPILE)
server:				$(lastword $(TEST_OBJ));	$(COMPILE)
tests:				all
tests: 				LDFLAGS += -L. -lmyprotocol
tests:				client server

-include $(DG_DEP)
$(DEBUG):			CFLAGS += -g -DDEBUG
$(DEBUG):			$(DG_OBJ); 	$(COMPILE_LIB)
debug:				$(DEBUG)

tests_run:			tests_functional tests_unit
	gcovr $(UT_DIR_OBJ) --exclude tests/
	gcovr $(UT_DIR_OBJ) --exclude tests/ --branches

clean:
	@[ -d $(DIR_BUILD) ]											\
	&& $(RM) $(DIR_BUILD)											\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(DIR_BUILD) || true

fclean:				clean
	@[ -f $(NAME) ]													\
	&& $(RM) $(NAME)												\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(NAME) || true
	@[ -f client ]													\
	&& $(RM) client													\
	&& printf "\033[31m[DELETED]\033[0m %s\n" client || true
	@[ -f server ]													\
	&& $(RM) server													\
	&& printf "\033[31m[DELETED]\033[0m %s\n" server || true

re:					fclean all

.PHONY:				all tests debug clean fclean re doc

.SILENT:			all tests debug clean fclean re doc
