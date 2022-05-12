#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"
#include "programoptions/commandlineoptions.h"
#include "server/Server.h"

namespace ircserv
{

#ifdef IRC_LOGGER_DEFINED
static void InitializeLogger(void)
{
    static plog::RollingFileAppender<plog::CsvFormatter> fileAppender("logs.csv", 1048576, 3);
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
#ifdef IRC_DEBUG
    plog::init(plog::debug, &fileAppender).addAppender(&consoleAppender);
#elif defined(IRC_RELEASE)
    plog::init(plog::info, &fileAppender).addAppender(&consoleAppender);
#endif
}
#endif // IRC_LOGGER_DEFINED

static void Initialize(void)
{
#ifdef IRC_LOGGER_DEFINED
    InitializeLogger();
#endif // IRC_LOGGER_DEFINED
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

       IRC_PLOGI << "Port: " << ircserv::GetCommandLineOptions().GetPort() << std::endl;
       IRC_PLOGI << "Password: " << ircserv::GetCommandLineOptions().GetPassword() << std::endl;
   }
   catch (const std::exception &x)
   {
       IRC_PLOGE << x.what() << std::endl;
       IRC_PLOGE << ircserv::GetCommandLineOptionsChecker().GetUsage() << std::endl;
       exitStatus = EXIT_FAILURE;
   }

   if (exitStatus == EXIT_SUCCESS)
   {
       servetLoop(atoi(argv[1]));
   }

   ircserv::Shutdown();
   return EXIT_SUCCESS;
}
