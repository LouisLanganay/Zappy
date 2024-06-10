##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

NAME		:=	zappy_server
EXT			:=	.c

DIR			:=	src
SRC			:=	$(addprefix $(DIR)/,								\
					main.c											\
					server.c										\
					payload.c										\
					verbose.c										\
					ai.c											\
					gui.c											\
					team.c											\
				)

DIR			+=	src/gui
SRC			+=	$(addprefix $(lastword $(DIR))/,					\
					msz.c											\
					bct.c											\
					mct.c											\
					tna.c											\
					pnw.c											\
					ppo.c											\
					plv.c											\
					pin.c											\
					pex.c											\
					pbc.c											\
					sgt.c											\
					sst.c											\
					smg.c											\
					suc.c											\
					sbp.c											\
					pic.c											\
					pie.c											\
					pfk.c											\
					pdr.c											\
					pgt.c											\
					pdi.c											\
					enw.c											\
					ebo.c											\
					edi.c											\
					sgt.c											\
					sst.c											\
					seg.c											\
				)

DIR         +=	src/ai
SRC			+=	$(addprefix $(lastword $(DIR))/,					\
					broadcast_text.c								\
					connect_nbr.c									\
					death.c											\
					eject.c											\
					fork.c											\
					forward.c										\
					incantation.c									\
					inventory.c										\
					left.c											\
					look.c											\
					right.c											\
					set_object.c									\
					take_object.c									\
				)

DIR_BUILD	:=	build
DIR_BIN		:=	$(DIR_BUILD)/bin

DIR_OBJ		:=	$(DIR_BUILD)/obj
OBJ			:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(SRC))
DEP			:=	$(OBJ:.o=.d)

DG_DIR_OBJ	:=	$(DIR_BUILD)/debug
DG_OBJ		:=	$(patsubst %$(EXT),$(DG_DIR_OBJ)/%.o,$(SRC))
DG_DEP		:=	$(DG_OBJ:.o=.d)

DEBUG		:=	$(DIR_BIN)/$(NAME)_debug

RM			:=	rm -rf

CC			:=	gcc
CFLAGS		:=	-iquote./include -iquote../libs/protocol/include	\
				-Wall -Wextra
LDFLAGS		:=	-L../libs -lmyprotocol

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
$(UT_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)
$(DG_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)

define COMPILE
	$(CREATE_DIR)
	@$(CC) -o $@ $^ $(LDFLAGS)			 							\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@						\
	|| printf "\033[31m[ERROR]\033[0m %s\n"  $@
endef

-include $(DEP)
$(NAME):			$(OBJ); 	$(COMPILE)

-include $(DG_DEP)
$(DEBUG):			CFLAGS += -g -DDEBUG
$(DEBUG):			$(DG_OBJ); 	$(COMPILE)
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

re:					fclean all

.PHONY:				all tests tests_run debug clean fclean re doc

.SILENT:			all tests tests_run debug clean fclean re doc
