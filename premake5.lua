workspace "ft_irc"
    configurations { "Release", "Debug", "Profile", "Final" }

outputdir = "%{cfg.buildcfg}"

project "ircserv"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++98"
    toolset "clang"
    targetdir ("bin/" .. outputdir)
    objdir ("tmp/" .. outputdir)
    
    pchheader "source/main/precomp.h"
    pchsource "source/main/precomp.cpp"

    includedirs
    {
        "source"
    }

    files
    {
        "source/**.h",
        "source/**.cpp"
    }

    filter "configurations:Release"
        defines
        {
            "DEBUG",
            "IRC_RELEASE"
        }
        includedirs
        {
            "extern/logging/plog/include"
        }
        symbols "On"
        optimize "On"

    filter "configurations:Debug"
        defines
        {
            "DEBUG",
            "IRC_DEBUG"
        }
        includedirs
        {
            "extern/logging/plog/include"
        }
        symbols "On"
        optimize "Off"

    filter "configurations:Profile"
        defines
        {
            "NDEBUG",
            "IRC_PFOFILE"
        }
        symbols "Off"
        optimize "On"

    filter "configurations:Final"
        defines
        {
            "NDEBUG",
            "IRC_FINAL"
        }
        symbols "Off"
        optimize "On"
