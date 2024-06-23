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
					egg.c											\
					send.c											\
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
					broadcast.c										\
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
					set.c											\
					take.c											\
				)

DIR			+=	src/game
SRC			+= 	$(addprefix $(lastword $(DIR))/,					\
					game.c											\
					map.c											\
				)

UT_DIR		:=	../tests/mock
UT_SRC		:=	$(addprefix $(UT_DIR)/,								\
					protocol.c										\
				)

UT_DIR		+=	../tests/server
UT_SRC		+=	$(filter-out src/main.c, $(SRC))
UT_SRC		+=	$(addprefix $(lastword $(UT_DIR))/,					\
					verbose.c										\
					ai.c											\
					gui.c											\
					team.c											\
					payload.c										\
					server.c										\
				)

UT_DIR		+=	../tests/server/gui
UT_SRC		+=	$(addprefix $(lastword $(UT_DIR))/,					\
					bct.c											\
					ebo.c											\
					edi.c											\
					enw.c											\
					mct.c											\
					msz.c											\
					pbc.c											\
					pdi.c											\
					pdr.c											\
					pex.c											\
					pfk.c											\
					pgt.c											\
					pic.c											\
					pie.c											\
					pin.c											\
					plv.c											\
					pnw.c											\
					ppo.c											\
					sbp.c											\
					seg.c											\
					sgt.c											\
					smg.c											\
					sst.c											\
					suc.c											\
					tna.c											\
				)

UT_DIR		+=	../tests/server/ai
UT_SRC		+=	$(addprefix $(lastword $(UT_DIR))/,					\
					death.c											\
					broadcast.c										\
					connect_nbr.c									\
					forward.c										\
					right.c											\
					left.c											\
					inventory.c										\
					look.c											\
					incantation.c									\
					take.c											\
					set.c											\
				)

DIR_BUILD	:=	build
DIR_BIN		:=	$(DIR_BUILD)/bin

DIR_OBJ		:=	$(DIR_BUILD)/obj
OBJ			:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(SRC))
DEP			:=	$(OBJ:.o=.d)

UT_DIR_OBJ	:=	$(DIR_BUILD)/tests/unit
UT_OBJ		:=	$(patsubst %$(EXT),$(UT_DIR_OBJ)/%.o,$(UT_SRC))
UT_DEP		:=	$(UT_OBJ:.o=.d)

DG_DIR_OBJ	:=	$(DIR_BUILD)/debug
DG_OBJ		:=	$(patsubst %$(EXT),$(DG_DIR_OBJ)/%.o,$(SRC))
DG_DEP		:=	$(DG_OBJ:.o=.d)

DEBUG		:=	$(DIR_BIN)/$(NAME)_debug
UT_TEST		:=	$(DIR_BIN)/unit_test

RM			:=	rm -rf

CC			:=	gcc
CFLAGS		:=	-iquote./include -iquote../libs/protocol/include	\
				-Wall -Wextra -g
LDFLAGS		:=	-L../libs -lmyprotocol

all:				$(NAME)

define CREATE_DIR
	@if [ ! -d $(dir $@) ]; then									\
		mkdir -p $(dir $@) 											\
		&& printf "\e[93m[CREATED]\e[0m %s\n" $(dir $@)				\
		|| printf "\e[31m[ERROR]\e[0m %s\n"   $(dir $@);			\
	fi
endef

define BUILD_OBJ
	@$(RM) $(patsubst %.o,%.gcda,$@)
	@$(RM) $(patsubst %.o,%.gcno,$@)
	$(CREATE_DIR)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@								\
	&& printf "\e[32m[OK]\e[0m %s\n" $<								\
	|| printf "\e[31m[KO]\e[0m %s\n" $<
endef

$(DIR_OBJ)/%.o:		%$(EXT); $(BUILD_OBJ)
$(UT_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)
$(DG_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)

define COMPILE
	$(CREATE_DIR)
	@$(CC) -o $@ $^ $(LDFLAGS)			 							\
	&& printf "\e[32m[SUCCES]\e[0m %s\n" $@							\
	|| printf "\e[31m[ERROR]\e[0m %s\n"  $@
endef

-include $(DEP)
$(NAME):			$(OBJ); 	$(COMPILE)

-include $(DG_DEP)
$(DEBUG):			CFLAGS += -g -DDEBUG
$(DEBUG):			$(DG_OBJ); 	$(COMPILE)
debug:				$(DEBUG)

-include $(UT_DEP)
$(UT_TEST):			CFLAGS += --coverage	 							\
				  -Dprotocol_server_send=mock_protocol_server_send		\
				  -Dprotocol_server_create=mock_protocol_server_create	\
				  -Dprotocol_server_is_open=mock_protocol_server_is_open
$(UT_TEST):			LDFLAGS += -lcriterion --coverage
$(UT_TEST):			$(UT_OBJ);	$(COMPILE)
tests_unit:			$(UT_TEST)
	@cp $(UT_TEST) $(UT_DIR_OBJ)
	@$(UT_DIR_OBJ)/$(notdir $<)

tests_run:			tests_unit
	gcovr $(UT_DIR_OBJ) --exclude tests/
	gcovr $(UT_DIR_OBJ) --exclude tests/ --txt-metric branch

clean:
	@[ -d $(DIR_BUILD) ]											\
	&& $(RM) $(DIR_BUILD)											\
	&& printf "\e[31m[DELETED]\e[0m %s\n" $(DIR_BUILD) || true

fclean:				clean
	@[ -f $(NAME) ]													\
	&& $(RM) $(NAME)												\
	&& printf "\e[31m[DELETED]\e[0m %s\n" $(NAME) || true

re:					fclean all

.PHONY:				all tests tests_run debug clean fclean re doc

.SILENT:			all tests tests_run debug clean fclean re doc
