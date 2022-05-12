#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"
#include "programoptions/commandlineoptions.h"
#include "server/Server.h"

namespace ircserv
{

#ifdef IRC_LOGGER_INITIALIZED
static void InitializeLogger(void)
{
#ifdef IRC_DEBUG
    plog::init(plog::debug, "logs_debug.txt");
#elif defined(IRC_RELEASE)
    plog::init(plog::info, "logs_release.txt");
#endif
}
#endif // IRC_LOGGER_INITIALIZED

static void Initialize(void)
{
#ifdef IRC_LOGGER_INITIALIZED
    InitializeLogger();
#endif // IRC_LOGGER_INITIALIZED

    CommandLineOptionsChecker::CreateSingleton();
    CommandLineOptions::CreateSingleton();
}

static void Shutdown(void)
{
    CommandLineOptions::DestroySingleton();
    CommandLineOptionsChecker::DestroySingleton();
}

}

void servetLoop(int port) {
    Server serv(port);

    while (true) {
        serv.accept_conn();
        serv.recv_from_client();
    }
}

int main(int argc, const char* argv[])
{
   int exitStatus = EXIT_SUCCESS;

   ircserv::Initialize();
   try
   {
       ircserv::GetCommandLineOptionsChecker().Check(argc, argv);
       servetLoop(atoi(argv[1]));
   }
   catch (const std::exception &x)
   {
       std::cerr << x.what() << '\n';
       std::cerr << ircserv::GetCommandLineOptionsChecker().GetUsage() << std::endl;
       exitStatus = EXIT_FAILURE;
   }
   ircserv::Shutdown();
   return EXIT_SUCCESS;
}
