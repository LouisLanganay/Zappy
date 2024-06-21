##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

NAME		:=	libmyprotocol.a
EXT			:=	.c

DIR			:=	src/client
SRC			:=	$(addprefix $(lastword $(DIR))/,					\
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

UF_DIR		:=	tests
UF_SRC		:=	$(addprefix $(UF_DIR)/,								\
					client.c										\
					server.c										\
				)

UT_DIR		:=	../../tests/protocol
UT_SRC		:=	$(SRC)
UT_SRC		+=	$(addprefix $(UT_DIR)/,								\
					client.c										\
					server.c										\
				)

DIR_BUILD	:=	build
DIR_BIN		:=	$(DIR_BUILD)/bin

DIR_OBJ		:=	$(DIR_BUILD)/obj
OBJ			:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(SRC))
DEP			:=	$(OBJ:.o=.d)

UF_OBJ		:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(UF_SRC))
UF_DEP		:=	$(UF_OBJ:.o=.d)

UT_DIR_OBJ	:=	$(DIR_BUILD)/tests/unit
UT_OBJ		:=	$(patsubst %$(EXT),$(UT_DIR_OBJ)/%.o,$(UT_SRC))
UT_DEP		:=	$(UT_OBJ:.o=.d)

DG_DIR_OBJ	:=	$(DIR_BUILD)/debug
DG_OBJ		:=	$(patsubst %$(EXT),$(DG_DIR_OBJ)/%.o,$(SRC))
DG_DEP		:=	$(DG_OBJ:.o=.d)

DEBUG		:=	$(DIR_BIN)/debug
UT_TEST		:=	$(DIR_BIN)/unit_test

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
$(UT_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)

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

-include $(DG_DEP)
$(DEBUG):			CFLAGS += -g -DDEBUG
$(DEBUG):			$(DG_OBJ); 	$(COMPILE_LIB)
debug:				$(DEBUG)

-include $(UF_DEP)
client:				$(firstword $(UF_OBJ));	$(COMPILE)
server:				$(lastword $(UF_OBJ));	$(COMPILE)
tests_functional:				all
tests_functional: 				LDFLAGS += -L. -lmyprotocol
tests_functional:				client server

-include $(UT_DEP)
$(UT_TEST):			CFLAGS += --coverage
$(UT_TEST):			LDFLAGS += -lcriterion --coverage
$(UT_TEST):			$(UT_OBJ);	$(COMPILE)
tests_unit:			$(UT_TEST)
	@cp $(UT_TEST) $(UT_DIR_OBJ)
	@$(UT_DIR_OBJ)/$(notdir $<)

tests_run:			tests_functional tests_unit
	gcovr $(UT_DIR_OBJ) --exclude tests/
	gcovr $(UT_DIR_OBJ) --exclude tests/ --txt-metric branch

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
