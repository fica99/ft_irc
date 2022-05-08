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

int main(int argc, const char* argv[])
{

    Server serv(2222);

    while (true) {
        serv.accept_conn();
        serv.recv_from_client();
    }

    return 0;
//    int exitStatus = EXIT_SUCCESS;
//    ircserv::Initialize();
//    try
//    {
//        ircserv::GetCommandLineOptionsChecker().Check(argc, argv);
//    }
//    catch (const std::exception &x)
//    {
//        std::cerr << x.what() << '\n';
//        std::cerr << ircserv::GetCommandLineOptionsChecker().GetUsage() << std::endl;
//        exitStatus = EXIT_FAILURE;
//    }
//    ircserv::Shutdown();
//    return EXIT_SUCCESS;
}
