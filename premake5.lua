workspace "OpenGL-Project"
	architecture "x64"
	startproject "OpenGL-Project"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "OpenGL-Project"
	location "OpenGL-Project"
    kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("obj/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"vendor/include",
		"vendor/include/gl",      
        "vendor/include/glfw"     
	}

	libdirs
	{
		"vendor/libs/gl", 
    	"vendor/libs/glfw" 
	}

	links
	{
		"glfw3", 
		"opengl32",            
    	"glew32"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"

	filter "configurations:Debug"
		defines "LQD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LQD_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "LQD_DIST"
		symbols "On"
