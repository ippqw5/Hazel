-- premake5.lua
workspace "Hazel" 

	architecture "x64"



	configurations

	{

	"Debug",

	"Release",

	"Dist"

	}



outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/GLFW/include"

include "Hazel/GLFW"

project "Hazel"

	location "Hazel"

	kind "SharedLib"

	language "C++"



	targetdir("bin/" .. outputdir .. "/%{prj.name}")

	objdir("bin/int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{

		"%{prj.name}/src/**.h",

		"%{prj.name}/src/**.cpp",

		"%{prj.name}/src/**.hpp"

	}



	includedirs

	{
		"%{prj.name}/src",
		"%{prj.name}/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"

		cppdialect "C++17"

		staticruntime "On"

		systemversion "latest"



		defines

		{
			"HZ_ENABLE_ASSERTS",

			"HZ_PLATFORM_WINDOWS",

			"HZ_BUILD_DLL",

			"_WINDLL",

		}



		postbuildcommands

		{

			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .."/SandBox")

		}



	filter "configurations:Debug"

		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	



	filter "configurations:Release"

		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "On"





	filter "configurations:Dist"

		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "On"



project "SandBox"

	location "SandBox"

	kind "ConsoleApp"

	language "C++"



	targetdir("bin/" .. outputdir .. "/%{prj.name}")

	objdir("bin/int/" .. outputdir .. "/%{prj.name}")



	files

	{

		"%{prj.name}/src/**.h",

		"%{prj.name}/src/**.cpp",

		"%{prj.name}/src/**.hpp"

	}



	includedirs

	{
		
		"Hazel/spdlog/include",

		"Hazel/src" 

	}



	links

	{

		"Hazel"

	}



	filter "system:windows"

		cppdialect "C++17"

		staticruntime "On"

		systemversion "latest"



		defines

		{

			"HZ_PLATFORM_WINDOWS",

		}



	filter "configurations:Debug"

		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	



	filter "configurations:Release"

		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "On"





	filter "configurations:Dist"

		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "On"