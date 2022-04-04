#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"
#include "programoptions/commandlineoptions.h"

namespace ircserv
{

static void Initialize(void)
{
    CommandLineOptionsChecker::CreateSingleton();
    CommandLineOptions::CreateSingleton();
}

static void Shutdown(void)
{
    CommandLineOptionsChecker::DestroySingleton();
    CommandLineOptions::DestroySingleton();
}

}

int main(int argc, const char* argv[])
{
    int exitStatus = EXIT_SUCCESS;
    ircserv::Initialize();
    try {
        ircserv::popGetCommandLineOptionsChecker().Check(argc, argv);
    } catch (const std::exception &x) {
        std::cerr << x.what() << '\n';
        std::cerr << ircserv::popGetCommandLineOptionsChecker().GetUsage() << std::endl;
        exitStatus = EXIT_FAILURE;
    }
    ircserv::Shutdown();
    return EXIT_SUCCESS;
}
