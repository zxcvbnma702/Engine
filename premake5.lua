workspace "Algernon"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Algernon/vendor/GLFW/include"
IncludeDir["Glad"] = "Algernon/vendor/Glad/include"
IncludeDir["ImGui"] = "Algernon/vendor/imgui"
IncludeDir["glm"] = "Algernon/vendor/glm"

group "Dependencies"
	include "Algernon/vendor/GLFW"
	include "Algernon/vendor/Glad"
	include "Algernon/vendor/imgui"

group ""

project "Algernon"
	location "Algernon"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Alpch.h"
	pchsource "Algernon/src/Alpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"AL_PLATFORM_WINDOWS",
			"AL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "AL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "AL_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Algernon/vendor/spdlog/include",
		"Algernon/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Algernon"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"AL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "AL_DIST"
		runtime "Release"
		optimize "On"