.NOTPARALLEL:

ifndef config
  config=final
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),final)
  ircserv_config = final
endif

NAME := ircserv

.PHONY: all clean fclean re help $(NAME) 

all: $(NAME)

$(NAME):
ifneq (,$(ircserv_config))
	@echo "==== Building ircserv ($(ircserv_config)) ===="
	@${MAKE} --no-print-directory -C . -f ircserv.make config=$(ircserv_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f ircserv.make clean

fclean:
	@${MAKE} --no-print-directory -C . -f ircserv.make clean
	@$(RM) -rf $(NAME)

re:
	@${MAKE} --no-print-directory -C . fclean
	@${MAKE} --no-print-directory -C . $(NAME)

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  final"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   fclean"
	@echo "   re"
	@echo "   ircserv"
