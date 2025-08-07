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
IncludeDir["glm"] = "Pack/vendor/glm"

include "Pack/vendor/GLFW"
include "Pack/vendor/Glad"
include "Pack/vendor/imgui"


project "Pack"
    location "Pack"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "Packpch.h"
    pchsource "Pack/src/Packpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    


    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PACK_PLATFORM_WINDOWS",
            "PACK_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        
        buildoptions { "/utf-8" }


    filter "configurations:Debug"
        defines "PACK_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PACK_RELEASE"
        runtime "Release"
        optimize "on"
        

    filter "configurations:Dist"
        defines "PACK_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

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
        "Pack/src",
        "%{IncludeDir.glm}",
        "Pack/vendor"
    }

    links
    {
        "Pack"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PACK_PLATFORM_WINDOWS"
        }

        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines "PACK_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PACK_RELEASE"
        runtime "Release"
        optimize "on"
        
    filter "configurations:Dist"
        defines "PACK_DIST"
        runtime "Release"
        optimize "on"
