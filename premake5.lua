-- premake5.lua

workspace "Pearl"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pearl"
	location "Pearl"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"


		defines
		{
			"PRL_PLATFORM_WINDOWS",
			"PRL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "HZ_DIST"
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
		"Pearl/vendor/spdlog/include",
		"Pearl/src"
	}

	links
	{
		"Pearl"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"


		defines
		{
			"PRL_PLATFORM_WINDOWS"
			
		}


	filter "configurations:Debug"
		defines "PRL_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "PRL_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "PRL_DIST"
		optimize "On"