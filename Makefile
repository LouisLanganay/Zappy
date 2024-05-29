##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

include Makefile_colors.mk

SERVER		=	zappy_server
SERVER_DIR	=	Server
GUI			=	zappy_gui
GUI_DIR		=	Client
AI			=	zappy_ai
AI_DIR		=	IA

LIBS		=	libmyprotocol.a
LIBS_DIR	=	libs/protocol

OUTS		=	$(SERVER) $(GUI) $(AI) $(LIBS)
DEPS		=	$(SERVER_DIR) $(GUI_DIR) $(AI_DIR) $(LIBS_DIR)

DIE         = exit 1
ECHO        = echo -e

define MAKE_DEPS
	@for dep in $^; do														\
		if [ -f $$dep/Makefile ]; then 										\
			$(ECHO) "${_B_YELLOW}[INFO]${_END} Making $@ in $$dep..."; 		\
			$(MAKE) -sC $$dep $@; 											\
			if [ -f $$dep/$@ ]; then 										\
				mv $$dep/$@ $$dep/../; 										\
			fi 																\
		else 																\
			$(ECHO) "${_B_YELLOW}[WARNING]${_END}" 	 						\
				"$$dep/Makefile not found, skipping...";					\
		fi 																	\
	done
endef

all: 		$(LIBS) $(SERVER) $(GUI) $(AI)
	@$(ECHO) "${_B_GREEN}[SUCCESS]${_END} project compiled successfully !"

$(SERVER): 	$(SERVER_DIR)	; $(MAKE_DEPS)
$(GUI): 	$(GUI_DIR)		; $(MAKE_DEPS)
$(AI): 		$(AI_DIR)		; $(MAKE_DEPS)
$(LIBS):  	$(LIBS_DIR)		; $(MAKE_DEPS)

debug: 		$(DEPS)			; $(MAKE_DEPS)
	@$(ECHO) "${_B_GREEN}[SUCCESS]${_END}"									\
		"project compiled successfully in debug mode !"
clean: 		$(DEPS)			; $(MAKE_DEPS)
	@$(ECHO) "${_B_GREEN}[SUCCESS]${_END} project cleaned successfully !"
fclean:		$(DEPS)			; $(MAKE_DEPS)
	@for out in $(realpath $(join $(addsuffix /../, $(DEPS)), $(OUTS))); do \
		if [ -f $$out ]; then 												\
			$(ECHO) "${_B_YELLOW}[INFO]${_END} Removing $${out##*/}..."; 	\
			rm -f $$out; 													\
		fi 																	\
	done
>>>>>>> 9a3e387 (fix(Makefile): fclean not working.)

re: fclean all

.PHONY: all $(SERVER) $(GUI) $(AI) $(LIBS) debug clean fclean re
