# GNU Make workspace makefile autogenerated by Premake

.NOTPARALLEL:

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),release)
  ircserv_config = release
endif
ifeq ($(config),debug)
  ircserv_config = debug
endif
ifeq ($(config),profile)
  ircserv_config = profile
endif
ifeq ($(config),final)
  ircserv_config = final
endif

PROJECTS := ircserv

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

ircserv:
ifneq (,$(ircserv_config))
	@echo "==== Building ircserv ($(ircserv_config)) ===="
	@${MAKE} --no-print-directory -C . -f ircserv.make config=$(ircserv_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f ircserv.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  release"
	@echo "  debug"
	@echo "  profile"
	@echo "  final"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   ircserv"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"