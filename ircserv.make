ifndef config
  config=final
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

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
  TARGETDIR = .
  TARGET = $(TARGETDIR)/ircserv
  OBJDIR = tmp
  PCH = source/main/precomp.h
  GCH = $(OBJDIR)/$(notdir $(PCH)).gch
  DEFINES += -DNDEBUG -DIRC_FINAL
  INCLUDES += -Isource
  FORCE_INCLUDE += -include $(OBJDIR)/$(notdir $(PCH))
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2 -Wall -Wextra -Werror
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2 -std=c++98 -Wall -Wextra -Werror
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
	$(OBJDIR)/ircchannel.o \
	$(OBJDIR)/ircclient.o \
	$(OBJDIR)/irccommand.o \
	$(OBJDIR)/irccommandsfactory.o \
	$(OBJDIR)/irccommandshelper.o \
	$(OBJDIR)/ircinvitecommand.o \
	$(OBJDIR)/ircjoincommand.o \
	$(OBJDIR)/irckickcommand.o \
	$(OBJDIR)/irclistcommand.o \
	$(OBJDIR)/ircnamescommand.o \
	$(OBJDIR)/ircnickcommand.o \
	$(OBJDIR)/ircnoticecommand.o \
	$(OBJDIR)/ircopercommand.o \
	$(OBJDIR)/ircpartcommand.o \
	$(OBJDIR)/ircpasscommand.o \
	$(OBJDIR)/ircprivmsgcommand.o \
	$(OBJDIR)/ircquitcommand.o \
	$(OBJDIR)/irctopiccommand.o \
	$(OBJDIR)/ircusercommand.o \
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
	$(OBJDIR)/ircresponseerr_nomotd.o \
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
	$(OBJDIR)/ircresponseerr_notregistered.o \
	$(OBJDIR)/ircresponseerr_passwdmismatch.o \
	$(OBJDIR)/ircresponseerr_toomanychannels.o \
	$(OBJDIR)/ircresponseerr_toomanytargets.o \
	$(OBJDIR)/ircresponseerr_unknowncommand.o \
	$(OBJDIR)/ircresponseerr_useronchannel.o \
	$(OBJDIR)/ircresponseerr_wildtoplevel.o \
	$(OBJDIR)/ircresponserpl_away.o \
	$(OBJDIR)/ircresponserpl_endofmotd.o \
	$(OBJDIR)/ircresponserpl_endofnames.o \
	$(OBJDIR)/ircresponserpl_inviting.o \
	$(OBJDIR)/ircresponserpl_list.o \
	$(OBJDIR)/ircresponserpl_listend.o \
	$(OBJDIR)/ircresponserpl_liststart.o \
	$(OBJDIR)/ircresponserpl_motd.o \
	$(OBJDIR)/ircresponserpl_motdstart.o \
	$(OBJDIR)/ircresponserpl_namreply.o \
	$(OBJDIR)/ircresponserpl_notopic.o \
	$(OBJDIR)/ircresponserpl_topic.o \
	$(OBJDIR)/ircresponserpl_umodeis.o \
	$(OBJDIR)/ircresponserpl_youreoper.o \
	$(OBJDIR)/ircresponsesfactory.o \
	$(OBJDIR)/ircresponseshelper.o \
	$(OBJDIR)/ircserver.o \
	$(OBJDIR)/ircsocket.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/precomp.o \
	$(OBJDIR)/ircchannelsmanager.o \
	$(OBJDIR)/ircclientsmanager.o \
	$(OBJDIR)/irccommandsmanager.o \
	$(OBJDIR)/ircparsinghelper.o \
	$(OBJDIR)/irclexer.o \
	$(OBJDIR)/ircparser.o \
	$(OBJDIR)/ircargtoken.o \
	$(OBJDIR)/irccommandtoken.o \
	$(OBJDIR)/ircprefixtoken.o \
	$(OBJDIR)/irctoken.o \
	$(OBJDIR)/irctokensfactory.o \
	$(OBJDIR)/commandlineoptionparams.o \
	$(OBJDIR)/commandlineoptionpasswordparams.o \
	$(OBJDIR)/commandlineoptionportparams.o \
	$(OBJDIR)/commandlineoptions.o \
	$(OBJDIR)/commandlineoptionschecker.o \
	$(OBJDIR)/irclogsinitializer.o \

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
	$(SILENT) rm -rf $(OBJDIR)
else
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

$(OBJDIR)/ircchannel.o: source/ircchannel/ircchannel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircclient.o: source/ircclient/ircclient.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommand.o: source/irccommands/irccommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommandsfactory.o: source/irccommands/irccommandsfactory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommandshelper.o: source/irccommands/irccommandshelper.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircinvitecommand.o: source/irccommands/ircinvitecommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircjoincommand.o: source/irccommands/ircjoincommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irckickcommand.o: source/irccommands/irckickcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irclistcommand.o: source/irccommands/irclistcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircnamescommand.o: source/irccommands/ircnamescommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircnickcommand.o: source/irccommands/ircnickcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircnoticecommand.o: source/irccommands/ircnoticecommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircopercommand.o: source/irccommands/ircopercommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircpartcommand.o: source/irccommands/ircpartcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircpasscommand.o: source/irccommands/ircpasscommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircprivmsgcommand.o: source/irccommands/ircprivmsgcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircquitcommand.o: source/irccommands/ircquitcommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irctopiccommand.o: source/irccommands/irctopiccommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircusercommand.o: source/irccommands/ircusercommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponse.o: source/ircresponses/ircresponse.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_alreadyregistered.o: source/ircresponses/ircresponseerr_alreadyregistered.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_badchannelkey.o: source/ircresponses/ircresponseerr_badchannelkey.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_bannedfromchan.o: source/ircresponses/ircresponseerr_bannedfromchan.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_cannotsendtochan.o: source/ircresponses/ircresponseerr_cannotsendtochan.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_cantkillserver.o: source/ircresponses/ircresponseerr_cantkillserver.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_channelisfull.o: source/ircresponses/ircresponseerr_channelisfull.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_chanoprivsneeded.o: source/ircresponses/ircresponseerr_chanoprivsneeded.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_erroneusnickname.o: source/ircresponses/ircresponseerr_erroneusnickname.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_inviteonlychan.o: source/ircresponses/ircresponseerr_inviteonlychan.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_needmoreparams.o: source/ircresponses/ircresponseerr_needmoreparams.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nickcollision.o: source/ircresponses/ircresponseerr_nickcollision.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nicknameinuse.o: source/ircresponses/ircresponseerr_nicknameinuse.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nomotd.o: source/ircresponses/ircresponseerr_nomotd.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nonicknamegiven.o: source/ircresponses/ircresponseerr_nonicknamegiven.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nooperhost.o: source/ircresponses/ircresponseerr_nooperhost.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_noprivileges.o: source/ircresponses/ircresponseerr_noprivileges.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_norecipient.o: source/ircresponses/ircresponseerr_norecipient.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nosuchchannel.o: source/ircresponses/ircresponseerr_nosuchchannel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nosuchnick.o: source/ircresponses/ircresponseerr_nosuchnick.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_nosuchserver.o: source/ircresponses/ircresponseerr_nosuchserver.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_notexttosend.o: source/ircresponses/ircresponseerr_notexttosend.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_notonchannel.o: source/ircresponses/ircresponseerr_notonchannel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_notoplevel.o: source/ircresponses/ircresponseerr_notoplevel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_notregistered.o: source/ircresponses/ircresponseerr_notregistered.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_passwdmismatch.o: source/ircresponses/ircresponseerr_passwdmismatch.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_toomanychannels.o: source/ircresponses/ircresponseerr_toomanychannels.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_toomanytargets.o: source/ircresponses/ircresponseerr_toomanytargets.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_unknowncommand.o: source/ircresponses/ircresponseerr_unknowncommand.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_useronchannel.o: source/ircresponses/ircresponseerr_useronchannel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseerr_wildtoplevel.o: source/ircresponses/ircresponseerr_wildtoplevel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_away.o: source/ircresponses/ircresponserpl_away.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_endofmotd.o: source/ircresponses/ircresponserpl_endofmotd.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_endofnames.o: source/ircresponses/ircresponserpl_endofnames.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_inviting.o: source/ircresponses/ircresponserpl_inviting.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_list.o: source/ircresponses/ircresponserpl_list.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_listend.o: source/ircresponses/ircresponserpl_listend.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_liststart.o: source/ircresponses/ircresponserpl_liststart.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_motd.o: source/ircresponses/ircresponserpl_motd.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_motdstart.o: source/ircresponses/ircresponserpl_motdstart.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_namreply.o: source/ircresponses/ircresponserpl_namreply.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_notopic.o: source/ircresponses/ircresponserpl_notopic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_topic.o: source/ircresponses/ircresponserpl_topic.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_umodeis.o: source/ircresponses/ircresponserpl_umodeis.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponserpl_youreoper.o: source/ircresponses/ircresponserpl_youreoper.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponsesfactory.o: source/ircresponses/ircresponsesfactory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircresponseshelper.o: source/ircresponses/ircresponseshelper.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircserver.o: source/ircserver/ircserver.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircsocket.o: source/ircserver/ircsocket.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/main.o: source/main/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/precomp.o: source/main/precomp.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircchannelsmanager.o: source/managers/ircchannelsmanager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircclientsmanager.o: source/managers/ircclientsmanager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommandsmanager.o: source/managers/irccommandsmanager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircparsinghelper.o: source/parsing/ircparsinghelper.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irclexer.o: source/parsing/lexer/irclexer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircparser.o: source/parsing/parser/ircparser.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircargtoken.o: source/parsing/tokens/ircargtoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irccommandtoken.o: source/parsing/tokens/irccommandtoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ircprefixtoken.o: source/parsing/tokens/ircprefixtoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irctoken.o: source/parsing/tokens/irctoken.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/irctokensfactory.o: source/parsing/tokens/irctokensfactory.cpp
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
$(OBJDIR)/irclogsinitializer.o: source/utils/logs/irclogsinitializer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif
