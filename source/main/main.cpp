#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"
#include "programoptions/commandlineoptions.h"

#include "ircmessages/lexer/irclexer.h"
#include "ircmessages/parser/ircparser.h"
#include "ircmessages/tokens/irctoken.h"
#include "ircmessages/tokens/irctokensfactory.h"
#include "irccommands/irccommand.h"
#include "irccommands/irccommandsfactory.h"


namespace ircserv
{

static void Initialize(void)
{
    CommandLineOptionsChecker::CreateSingleton();
    CommandLineOptions::CreateSingleton();

    IRCLexer::CreateSingleton();
    IRCLexerParams params =
    {
        .Prefix = ":",
        .TokensDelim = " ",
        .BlockDelim = ":"
    };
    GetIRCLexer().SetLexerParams(params);

    IRCParser::CreateSingleton();
}

static void Shutdown(void)
{
    IRCParser::DestroySingleton();
    IRCLexer::DestroySingleton();

    CommandLineOptions::DestroySingleton();
    CommandLineOptionsChecker::DestroySingleton();
}


}

int main(int argc, const char* argv[])
{
    int exitStatus = EXIT_SUCCESS;
    ircserv::Initialize();
    try
    {
        ircserv::GetCommandLineOptionsChecker().Check(argc, argv);
        std::string ss(":heloooo     PASS         test test2 :  test3 test4 test5 test6");
        std::vector<ircserv::IRCToken*> tokens = ircserv::GetIRCLexer().Tokenize(ss);
        ircserv::IRCCommand *command = ircserv::GetIRCParser().CreateCommand(tokens);
        command->ProcessCommand();
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
