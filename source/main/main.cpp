#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"
#include "programoptions/commandlineoptions.h"
#include "server/Server.h"
namespace ircserv
{

static void Initialize(void)
{
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
