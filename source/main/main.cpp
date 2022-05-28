#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"
#include "programoptions/commandlineoptions.h"
#include "ircserver/ircserver.h"
#include "managers/irccommandsmanager.h"
#include "utils/logs/irclogsinitializer.h"

namespace ircserv
{

static void Initialize(void)
{
    IRCLogsInitializer::CreateSingleton();
    CommandLineOptions::CreateSingleton();
    IRCCommandsManager::CreateSingleton();
    IRCServer::CreateSingleton();
}

static void Shutdown(void)
{
    IRCServer::DestroySingleton();
    IRCCommandsManager::DestroySingleton();
    CommandLineOptions::DestroySingleton();
    IRCLogsInitializer::DestroySingleton();
}

static void ServerLoop()
{
    IRCServer& serv = GetIRCServer();

    serv.SetPort(GetCommandLineOptions().GetPort());
    serv.SetPassword(GetCommandLineOptions().GetPassword());
    serv.SetServerName("IRC");
    serv.Start();
}

static bool CheckCommandLineOptions(int argc, const char **argv)
{
    CommandLineOptionsChecker checker;
    try
    {
        checker.Check(argc, argv);
        
        IRC_LOGD("Commandline option - port: %d", GetCommandLineOptions().GetPort());
        IRC_LOGD("Commandline option - password: %s", GetCommandLineOptions().GetPassword().c_str());
    }
    catch (const std::exception &x)
    {
        IRC_LOGE("%s", x.what());
        IRC_LOGE("%s", checker.GetUsage().c_str());
        return false;
    }
    return true;
}

}

int main(int argc, const char* argv[])
{
    int exitStatus = EXIT_SUCCESS;
    ircserv::Initialize();

    if (ircserv::CheckCommandLineOptions(argc, argv))
    {
        ircserv::ServerLoop();
    }
    else
    {
        exitStatus = EXIT_FAILURE;
    }

    ircserv::Shutdown();
    return exitStatus;
}
