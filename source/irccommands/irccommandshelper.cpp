#include "main/precomp.h"

#include "irccommands/irccommandshelper.h"

#include "ircresponses/ircresponse.h"
#include "ircresponses/ircresponseerr_erroneusnickname.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponseerr_nicknameinuse.h"
#include "ircresponses/ircresponseerr_nomotd.h"
#include "ircresponses/ircresponseerr_unknowncommand.h"
#include "ircresponses/ircresponserpl_endofmotd.h"
#include "ircresponses/ircresponserpl_motd.h"
#include "ircresponses/ircresponserpl_motdstart.h"
#include "ircresponses/ircresponses.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

void IRCCommandsHelper::SendResponseWithoutParams(IRCSocket *socket, Enum_IRCResponses responseEnum)
{
    IRCResponse* response = IRCResponsesFactory::CreateResponse(responseEnum);
    if (response != NULL)
    {
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendERR_NEEDMOREPARAMS(IRCSocket *socket, Enum_IRCCommands commandEnum)
{
    const std::string command = EnumString<Enum_IRCCommands>::From(commandEnum);
    IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
    );
    if (response != NULL)
    {
        response->SetCommand(command);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendERR_ERRONEUSNICKNAME(IRCSocket *socket, const std::string& nick)
{
    IRCResponseERR_ERRONEUSNICKNAME* response = dynamic_cast<IRCResponseERR_ERRONEUSNICKNAME*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_ERRONEUSNICKNAME)
    );
    if (response != NULL)
    {
        response->SetNick(nick);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendERR_NICKNAMEINUSE(IRCSocket *socket, const std::string& nick)
{
    IRCResponseERR_NICKNAMEINUSE *response = dynamic_cast<IRCResponseERR_NICKNAMEINUSE*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_NICKNAMEINUSE)
    );
    if (response != NULL)
    {
        response->SetNick(nick);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendRPL_MOTDSTART(IRCSocket *socket, const std::string server)
{
    IRCResponseRPL_MOTDSTART *response = dynamic_cast<IRCResponseRPL_MOTDSTART*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_MOTDSTART)
    );
    if (response != NULL)
    {
        response->SetServer(server);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendRPL_ENDOFMOTD(IRCSocket *socket)
{
    IRCResponseRPL_ENDOFMOTD *response = dynamic_cast<IRCResponseRPL_ENDOFMOTD*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_ENDOFMOTD)
    );
    if (response != NULL)
    {
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendRPL_MOTD(IRCSocket *socket, const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;

    if (file.good())
    {
        while (std::getline(file, line))
        {
            IRCResponseRPL_MOTD *response = dynamic_cast<IRCResponseRPL_MOTD*>(
                IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_MOTD)
            );
            if (response != NULL)
            {
                response->SetText(line);
                response->Send(socket);
            }
            IRCResponsesFactory::DestroyResponse(response);
        }
    }
    else
    {
        SendERR_NOMOTD(socket);
    }
}

void IRCCommandsHelper::SendERR_NOMOTD(IRCSocket *socket)
{
    IRCResponseERR_NOMOTD *response = dynamic_cast<IRCResponseERR_NOMOTD*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_NOMOTD)
    );
    if (response != NULL)
    {
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}


void IRCCommandsHelper::SendMOTD(IRCSocket *socket, const std::string server, const std::string& filename)
{
    IRCCommandsHelper::SendRPL_MOTDSTART(socket, server);
    IRCCommandsHelper::SendRPL_MOTD(socket, filename);
    IRCCommandsHelper::SendRPL_ENDOFMOTD(socket);
}

void IRCCommandsHelper::SendERR_UNKNOWNCOMMAND(IRCSocket *socket, const std::string& command)
{
    IRCResponseERR_UNKNOWNCOMMAND *response = dynamic_cast<IRCResponseERR_UNKNOWNCOMMAND*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_UNKNOWNCOMMAND)
    );
    if (response != NULL)
    {
        response->SetCommand(command);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}



}
