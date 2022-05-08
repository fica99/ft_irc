# GNU Make project makefile autogenerated by Premake

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

ifeq ($(config),release)
  ifeq ($(origin CC), default)
    CC = clang
  endif
  ifeq ($(origin CXX), default)
    CXX = clang++
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  TARGETDIR = bin/Release-linux
  TARGET = $(TARGETDIR)/ircserv
  OBJDIR = tmp/Release-linux
  PCH = source/main/precomp.h
  GCH = $(OBJDIR)/$(notdir $(PCH)).gch
  DEFINES += -DNDEBUG -DRELEASE
  INCLUDES += -Isource
  FORCE_INCLUDE += -include $(OBJDIR)/$(notdir $(PCH))
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2 -std=c++98
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS +=
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS)
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug)
  ifeq ($(origin CC), default)
    CC = clang
  endif
  ifeq ($(origin CXX), default)
    CXX = clang++
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  TARGETDIR = bin/Debug-linux
  TARGET = $(TARGETDIR)/ircserv
  OBJDIR = tmp/Debug-linux
  PCH = source/main/precomp.h
  GCH = $(OBJDIR)/$(notdir $(PCH)).gch
  DEFINES += -DDEBUG
  INCLUDES += -Isource
  FORCE_INCLUDE += -include $(OBJDIR)/$(notdir $(PCH))
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O0 -g
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O0 -g -std=c++98
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS +=
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS)
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),profile)
  ifeq ($(origin CC), default)
    CC = clang
  endif
  ifeq ($(origin CXX), default)
    CXX = clang++
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  TARGETDIR = bin/Profile-linux
  TARGET = $(TARGETDIR)/ircserv
  OBJDIR = tmp/Profile-linux
  PCH = source/main/precomp.h
  GCH = $(OBJDIR)/$(notdir $(PCH)).gch
  DEFINES += -DNDEBUG -DPFOFILE
  INCLUDES += -Isource
  FORCE_INCLUDE += -include $(OBJDIR)/$(notdir $(PCH))
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2 -std=c++98
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS +=
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS)
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),final)
  ifeq ($(origin CC), default)
    CC = clang
  endif
  ifeq ($(origin CXX), default)
    CXX = clang++
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  TARGETDIR = bin/Final-linux
  TARGET = $(TARGETDIR)/ircserv
  OBJDIR = tmp/Final-linux
  PCH = source/main/precomp.h
  GCH = $(OBJDIR)/$(notdir $(PCH)).gch
  DEFINES += -DFINAL
  INCLUDES += -Isource
  FORCE_INCLUDE += -include $(OBJDIR)/$(notdir $(PCH))
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2 -std=c++98
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS +=
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS)
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: prebuild prelink $(TARGET)
	@:

endif

OBJECTS := \
	$(OBJDIR)/main.o \
	$(OBJDIR)/precomp.o \
	$(OBJDIR)/commandlineoptionparams.o \
	$(OBJDIR)/commandlineoptionpasswordparams.o \
	$(OBJDIR)/commandlineoptionportparams.o \
	$(OBJDIR)/commandlineoptions.o \
	$(OBJDIR)/commandlineoptionschecker.o \
	$(OBJDIR)/irccommand.o \
	$(OBJDIR)/irccommandsfactory.o \
	$(OBJDIR)/ircjoincommand.o \
	$(OBJDIR)/irckickcommand.o \
	$(OBJDIR)/irckillcommand.o \
	$(OBJDIR)/irclistcommand.o \
	$(OBJDIR)/ircnamescommand.o \
	$(OBJDIR)/ircnickcommand.o \
	$(OBJDIR)/ircnoticecommand.o \
	$(OBJDIR)/ircopercommand.o \
	$(OBJDIR)/ircpartcommand.o \
	$(OBJDIR)/ircpasscommand.o \
	$(OBJDIR)/ircprivmsgcommand.o \
	$(OBJDIR)/ircquitcommand.o \
	$(OBJDIR)/ircusercommand.o \
	$(OBJDIR)/irccommandsmanager.o \
	$(OBJDIR)/irclexer.o \
	$(OBJDIR)/ircparser.o \
	$(OBJDIR)/ircargtoken.o \
	$(OBJDIR)/irccommandtoken.o \
	$(OBJDIR)/ircprefixtoken.o \
	$(OBJDIR)/irctoken.o \
	$(OBJDIR)/irctokensfactory.o \
	$(OBJDIR)/ircresponse.o \
	$(OBJDIR)/ircresponseerr_alreadyregistered.o \
	$(OBJDIR)/ircresponseerr_badchannelkey.o \
	$(OBJDIR)/ircresponseerr_bannedfromchan.o \
	$(OBJDIR)/ircresponseerr_cannotsendtochan.o \
	$(OBJDIR)/ircresponseerr_cantkillserver.o \
	$(OBJDIR)/ircresponseerr_channelisfull.o \
	$(OBJDIR)/ircresponseerr_chanoprivsneeded.o \
	$(OBJDIR)/ircresponseerr_erroneusnickname.o \
	$(OBJDIR)/ircresponseerr_inviteonlychan.o \
	$(OBJDIR)/ircresponseerr_needmoreparams.o \
	$(OBJDIR)/ircresponseerr_nickcollision.o \
	$(OBJDIR)/ircresponseerr_nicknameinuse.o \
	$(OBJDIR)/ircresponseerr_nonicknamegiven.o \
	$(OBJDIR)/ircresponseerr_nooperhost.o \
	$(OBJDIR)/ircresponseerr_noprivileges.o \
	$(OBJDIR)/ircresponseerr_norecipient.o \
	$(OBJDIR)/ircresponseerr_nosuchchannel.o \
	$(OBJDIR)/ircresponseerr_nosuchnick.o \
	$(OBJDIR)/ircresponseerr_nosuchserver.o \
	$(OBJDIR)/ircresponseerr_notexttosend.o \
	$(OBJDIR)/ircresponseerr_notonchannel.o \
	$(OBJDIR)/ircresponseerr_notoplevel.o \
	$(OBJDIR)/ircresponseerr_passwdmismatch.o \
	$(OBJDIR)/ircresponseerr_toomanychannels.o \
	$(OBJDIR)/ircresponseerr_toomanytargets.o \
	$(OBJDIR)/ircresponseerr_wildtoplevel.o \
	$(OBJDIR)/ircresponserpl_away.o \
	$(OBJDIR)/ircresponserpl_endofnames.o \
	$(OBJDIR)/ircresponserpl_list.o \
	$(OBJDIR)/ircresponserpl_listend.o \
	$(OBJDIR)/ircresponserpl_liststart.o \
	$(OBJDIR)/ircresponserpl_namreply.o \
	$(OBJDIR)/ircresponserpl_topic.o \
	$(OBJDIR)/ircresponserpl_youreoper.o \
	$(OBJDIR)/ircresponsesfactory.o \

RESOURCES := \

CUSTOMFILES := \

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

$(TARGET): $(GCH) ${CUSTOMFILES} $(OBJECTS) $(LDDEPS) $(RESOURCES) | $(TARGETDIR)
	@echo Linking ircserv
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(CUSTOMFILES): | $(OBJDIR)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning ircserv
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) $(PCH) | $(OBJDIR)
$(GCH): $(PCH) | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
else
$(OBJECTS): | $(OBJDIR)
endif

$(OBJDIR)/main.o: source/main/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/precomp.o: source/main/precomp.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/commandlineoptionparams.o: source/programoptions/commandlineoptionparams.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/commandlineoptionpasswordparams.o: source/programoptions/commandlineoptionpasswordparams.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/commandlineoptionportparams.o: source/programoptions/commandlineoptionportparams.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/commandlineoptions.o: source/programoptions/commandlineoptions.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/commandlineoptionschecker.o: source/programoptions/commandlineoptionschecker.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommand.o: source/server/commands/commands/irccommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommandsfactory.o: source/server/commands/commands/irccommandsfactory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircjoincommand.o: source/server/commands/commands/ircjoincommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irckickcommand.o: source/server/commands/commands/irckickcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irckillcommand.o: source/server/commands/commands/irckillcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irclistcommand.o: source/server/commands/commands/irclistcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircnamescommand.o: source/server/commands/commands/ircnamescommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircnickcommand.o: source/server/commands/commands/ircnickcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircnoticecommand.o: source/server/commands/commands/ircnoticecommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircopercommand.o: source/server/commands/commands/ircopercommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircpartcommand.o: source/server/commands/commands/ircpartcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircpasscommand.o: source/server/commands/commands/ircpasscommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircprivmsgcommand.o: source/server/commands/commands/ircprivmsgcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircquitcommand.o: source/server/commands/commands/ircquitcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircusercommand.o: source/server/commands/commands/ircusercommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommandsmanager.o: source/server/commands/manager/irccommandsmanager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irclexer.o: source/server/commands/parsing/lexer/irclexer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircparser.o: source/server/commands/parsing/parser/ircparser.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircargtoken.o: source/server/commands/parsing/tokens/ircargtoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommandtoken.o: source/server/commands/parsing/tokens/irccommandtoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircprefixtoken.o: source/server/commands/parsing/tokens/ircprefixtoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irctoken.o: source/server/commands/parsing/tokens/irctoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irctokensfactory.o: source/server/commands/parsing/tokens/irctokensfactory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponse.o: source/server/commands/responses/ircresponse.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_alreadyregistered.o: source/server/commands/responses/ircresponseerr_alreadyregistered.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_badchannelkey.o: source/server/commands/responses/ircresponseerr_badchannelkey.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_bannedfromchan.o: source/server/commands/responses/ircresponseerr_bannedfromchan.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_cannotsendtochan.o: source/server/commands/responses/ircresponseerr_cannotsendtochan.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_cantkillserver.o: source/server/commands/responses/ircresponseerr_cantkillserver.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_channelisfull.o: source/server/commands/responses/ircresponseerr_channelisfull.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_chanoprivsneeded.o: source/server/commands/responses/ircresponseerr_chanoprivsneeded.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_erroneusnickname.o: source/server/commands/responses/ircresponseerr_erroneusnickname.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_inviteonlychan.o: source/server/commands/responses/ircresponseerr_inviteonlychan.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_needmoreparams.o: source/server/commands/responses/ircresponseerr_needmoreparams.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nickcollision.o: source/server/commands/responses/ircresponseerr_nickcollision.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nicknameinuse.o: source/server/commands/responses/ircresponseerr_nicknameinuse.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nonicknamegiven.o: source/server/commands/responses/ircresponseerr_nonicknamegiven.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nooperhost.o: source/server/commands/responses/ircresponseerr_nooperhost.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_noprivileges.o: source/server/commands/responses/ircresponseerr_noprivileges.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_norecipient.o: source/server/commands/responses/ircresponseerr_norecipient.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nosuchchannel.o: source/server/commands/responses/ircresponseerr_nosuchchannel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nosuchnick.o: source/server/commands/responses/ircresponseerr_nosuchnick.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nosuchserver.o: source/server/commands/responses/ircresponseerr_nosuchserver.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_notexttosend.o: source/server/commands/responses/ircresponseerr_notexttosend.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_notonchannel.o: source/server/commands/responses/ircresponseerr_notonchannel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_notoplevel.o: source/server/commands/responses/ircresponseerr_notoplevel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_passwdmismatch.o: source/server/commands/responses/ircresponseerr_passwdmismatch.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_toomanychannels.o: source/server/commands/responses/ircresponseerr_toomanychannels.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_toomanytargets.o: source/server/commands/responses/ircresponseerr_toomanytargets.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_wildtoplevel.o: source/server/commands/responses/ircresponseerr_wildtoplevel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_away.o: source/server/commands/responses/ircresponserpl_away.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_endofnames.o: source/server/commands/responses/ircresponserpl_endofnames.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_list.o: source/server/commands/responses/ircresponserpl_list.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_listend.o: source/server/commands/responses/ircresponserpl_listend.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_liststart.o: source/server/commands/responses/ircresponserpl_liststart.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_namreply.o: source/server/commands/responses/ircresponserpl_namreply.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_topic.o: source/server/commands/responses/ircresponserpl_topic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_youreoper.o: source/server/commands/responses/ircresponserpl_youreoper.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponsesfactory.o: source/server/commands/responses/ircresponsesfactory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif