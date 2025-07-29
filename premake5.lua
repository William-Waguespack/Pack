workspace "Pack"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Pack/vendor/GLFW/include"
IncludeDir["Glad"] = "Pack/vendor/Glad/include"
IncludeDir["ImGui"] = "Pack/vendor/imgui"

include "Pack/vendor/GLFW"
include "Pack/vendor/Glad"
include "Pack/vendor/imgui"


project "Pack"
    location "Pack"
    kind "SharedLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "Packpch.h"
    pchsource "Pack/src/Packpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }


    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "PACK_PLATFORM_WINDOWS",
            "PACK_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        
        buildoptions { "/utf-8" }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "PACK_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PACK_RELEASE"
        runtime "Release"
        optimize "On"
        

    filter "configurations:Dist"
        defines "PACK_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Pack/vendor/spdlog/include",
        "Pack/src"
    }

    links
    {
        "Pack"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "PACK_PLATFORM_WINDOWS"
        }

        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines "PACK_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PACK_RELEASE"
        runtime "Release"
        optimize "On"
        
    filter "configurations:Dist"
        defines "PACK_DIST"
        runtime "Release"
        optimize "On"
