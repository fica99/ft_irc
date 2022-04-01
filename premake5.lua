workspace "ft_irc"
    configurations { "Release", "Debug", "Profile", "Final" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "ircserv"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++98"
    toolset "clang"
    targetdir ("bin/" .. outputdir)
    objdir ("tmp/" .. outputdir)
    
    files
    {
        "sources/**.h",
        "sources/**.cpp"
    }

    filter "configurations:Release"
        defines
        {
            "NDEBUG",
            "RELEASE"
        }
        optimize "On"

    filter "configurations:Debug"
        defines
        {
            "DEBUG"
        }
        symbols "On"
        optimize "Off"

    filter "configurations:Profile"
        defines
        {
            "NDEBUG",
            "PFOFILE"
        }
        optimize "On"

    filter "configurations:Final"
        defines
        {
            "FINAL"
        }
        optimize "On"
