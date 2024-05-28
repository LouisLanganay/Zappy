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

DEPS		=	$(SERVER_DIR) $(GUI_DIR) $(AI_DIR) $(LIBS_DIR)

DIE         = exit 1
ECHO        = echo -e

define MAKE_DEPS
	@for dep in $^; do \
		if [ -f $$dep/Makefile ]; then \
			$(ECHO) "${_B_YELLOW}[INFO]${_END} Making $@ in $$dep..."; \
			$(MAKE) -sC $$dep $@; \
			if [ -f $$dep/$@ ]; then \
				mv $$dep/$@ $$dep/../; \
			fi \
		else \
			$(ECHO) "${_B_YELLOW}[WARNING]${_END} $$dep/Makefile not found, skipping..."; \
		fi \
	done
endef

<<<<<<< HEAD
zappy_server:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -s -C Server; \
		mv Server/zappy_server ./zappy_server; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi

zappy_gui:
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -s -C Client; \
		mv Client/zappy_gui ./zappy_gui; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi

zappy_ai:
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -s -C IA; \
		mv IA/zappy_ai ./zappy_ai; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi

debug:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -s -C Server debug; \
		mv Server/zappy_server ./zappy_server; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -s -C Client debug; \
		mv Client/zappy_gui ./zappy_gui; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -s -C IA debug; \
		mv IA/zappy_ai ./zappy_ai; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi
clean:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -s -C Server clean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -s -C Client clean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -s -C IA clean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi

fclean:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -s -C Server fclean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -s -C Client fclean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -s -C IA fclean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi
	@rm -f zappy_server zappy_gui zappy_ai
=======
all: 		$(LIBS) $(SERVER) $(GUI) $(AI)
	@$(ECHO) "${_B_GREEN}[SUCCESS]${_END} project compiled successfully !"

$(SERVER): 	$(SERVER_DIR)	; $(MAKE_DEPS)
$(GUI): 	$(GUI_DIR)		; $(MAKE_DEPS)
$(AI): 		$(AI_DIR)		; $(MAKE_DEPS)
$(LIBS):  	$(LIBS_DIR)		; $(MAKE_DEPS)

debug: 		$(DEPS)			; $(MAKE_DEPS)
	@$(ECHO) "${_B_GREEN}[SUCCESS]${_END} project compiled successfully in debug mode !"
clean: 		$(DEPS)			; $(MAKE_DEPS)
	@$(ECHO) "${_B_GREEN}[SUCCESS]${_END} project cleaned successfully !"
fclean: 	$(DEPS)			; $(MAKE_DEPS)
>>>>>>> b0e8363 (build(libs): move libs to the root and simplified root Makefile.)

re: fclean all

.PHONY: all $(SERVER) $(GUI) $(AI) $(LIBS) debug clean fclean re
