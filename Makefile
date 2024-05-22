##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

include Makefile_colors.mk

DIE         = exit 1
ECHO        = echo -e

all: zappy_server zappy_gui zappy_ai
	@ $(ECHO) "${_B_GREEN}[SUCCESS]${_END} project compiled successfully !"

zappy_server:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -C Server; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi

zappy_gui:
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -C Client; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi

zappy_ai:
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -C IA; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi

debug:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -C Server debug; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -C Client debug; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -C IA debug; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi

clean:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -C Server clean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -C Client clean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -C IA clean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi

fclean:
	@if [ -f Server/Makefile ]; then \
		$(MAKE) -C Server fclean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Server/Makefile not found, skipping..."; \
	fi
	@if [ -f Client/Makefile ]; then \
		$(MAKE) -C Client fclean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} Client/Makefile not found, skipping..."; \
	fi
	@if [ -f IA/Makefile ]; then \
		$(MAKE) -C IA fclean; \
	else \
		$(ECHO) "${_B_YELLOW}[WARNING]${_END} IA/Makefile not found, skipping..."; \
	fi

re: fclean all

.PHONY: all zappy_server zappy_gui zappy_ai debug clean fclean re
