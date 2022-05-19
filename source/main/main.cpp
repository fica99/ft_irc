#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"
#include "programoptions/commandlineoptions.h"
#include "server/ircserver.h"
#include "utils/logs/irclogsinitializer.h"
#include <signal.h>
bool work = true;
namespace ircserv
{

static void Initialize(void)
{
    IRCLogsInitializer::CreateSingleton();
    CommandLineOptions::CreateSingleton();
}

static void Shutdown(void)
{
    CommandLineOptions::DestroySingleton();
    IRCLogsInitializer::DestroySingleton();
}

static void ServerLoop()
{
    IRCServer serv(GetCommandLineOptions().GetPort());

    IRC_LOGI("%s", "The server is running...");
    while (work)
    {
        serv.AcceptConn();
        serv.RecvFromClient();
    }
    IRC_LOGI("%s", "The server is stopped");
}

static bool CheckCommandLineOptions(int argc, const char **argv)
{
    CommandLineOptionsChecker checker;
    try
    {
        checker.Check(argc, argv);
        
        IRC_LOGI("Port: %d", GetCommandLineOptions().GetPort());
        IRC_LOGI("Password: %s", GetCommandLineOptions().GetPassword().c_str());
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

void	sigHandler(int signum)
{
	(void)signum;
	work = false;
}

int main(int argc, const char* argv[])
{
    int exitStatus = EXIT_SUCCESS;
    signal(SIGINT, &sigHandler);
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
