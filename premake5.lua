workspace "Scavenger"
	architecture "x64"

	configurations
	{
		"debug",
		"release"
	}

	startproject "Test00_Logger"

	bin_dir = "bin/%{cfg.buildcfg}/%{prj.name}/"
    obj_dir = ".build/%{cfg.buildcfg}/%{prj.name}/"
	lib_dir = "lib/%{cfg.buildcfg}/"

	test_bin_dir = "bin/%{cfg.buildcfg}/tests/%{prj.name}/"
	test_obj_dir = ".build/%{cfg.buildcfg}/tests/%{prj.name}/"

project "SgeCore"
	location "vs-projects/sgecore"
	kind "StaticLib"
	language "C++"
	targetdir(lib_dir)
    objdir(obj_dir)
	files
	{
		"source/%{prj.name}/**.h",
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"source/sgecore/"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"
		defines "SGE_WIN32"
			
	filter "configurations:debug"
		defines "SGE_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "SGE_RELEASE"
		optimize "On"


project "SgeEngine"
	location "vs-projects/sgeengine"
	kind "StaticLib"
	targetdir(lib_dir)
    objdir(obj_dir)
	files
	{
		"source/%{prj.name}/**.h",
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"source/sgecore/",
		"source/sgeengine/"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"
		defines "SGE_WIN32"
			
	filter "configurations:debug"
		defines "SGE_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "SGE_RELEASE"
		optimize "On"
	links
	{
		"SgeCore"
	}

project "SgeTest"
	location "vs-projects/sgetest"
	kind "StaticLib"
	targetdir(lib_dir)
    objdir(obj_dir)
	files
	{
		"source/%{prj.name}/**.h",
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"source/sgecore/",
		"source/sgeengine/",
		"source/sgetest/"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"
		defines "SGE_WIN32"
			
	filter "configurations:debug"
		defines "SGE_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "SGE_RELEASE"
		optimize "On"
	links
	{
		"SgeCore"
	}


project "SgeCreator"
	location "vs-projects/sgecreator"
	kind "ConsoleApp"
	language "C++"
	targetdir(bin_dir)
    objdir(obj_dir)
	files
	{
		"source/%{prj.name}/**.h",
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"source/sgecore/",
		"source/sgeengine/",
		"source/sgecreator/"
	}
	links
	{
		"SgeCore",
		"SgeEngine"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"
		defines "SGE_WIN32"
			
	filter "configurations:debug"
		defines "SGE_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "SGE_RELEASE"
		optimize "On"

project "Test00_Logger"
	location "vs-projects/tests/test00_logger"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir(test_bin_dir)
    objdir(test_obj_dir)
	staticruntime "on"
	files
	{
		"source/tests/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"source/sgecore/",
		"source/sgeengine/",
		"source/tests/test00_logger/"
	}
	libdirs
	{
		"libs/%{cfg.buildcfg}/"
		
	}
	links
	{
		"SgeCore"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"
		defines "SGE_WIN32"
			
	filter "configurations:debug"
		defines "SGE_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "SGE_RELEASE"
		optimize "On"


project "Test01_TestLib"
	location "vs-projects/tests/test01_testlib"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir(test_bin_dir)
    objdir(test_obj_dir)
	staticruntime "on"
	files
	{
		"source/tests/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"source/sgecore/",
		"source/sgetest/",
		"source/tests/test01_testlib/"
	}
	libdirs
	{
		"libs/%{cfg.buildcfg}/"
		
	}
	links
	{
		"SgeCore",
		"SgeTest"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"
		defines "SGE_WIN32"
			
	filter "configurations:debug"
		defines "SGE_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "SGE_RELEASE"
		optimize "On"

project "Test02_StringUtils"
	location "vs-projects/tests/test02_stringutils"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir(test_bin_dir)
    objdir(test_obj_dir)
	staticruntime "on"
	files
	{
		"source/tests/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"source/sgecore/",
		"source/tests/test01_testlib/"
	}
	libdirs
	{
		"libs/%{cfg.buildcfg}/"
		
	}
	links
	{
		"SgeCore"
	}
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"
		defines "SGE_WIN32"
			
	filter "configurations:debug"
		defines "SGE_DEBUG"
		symbols "On"

	filter "configurations:release"
		defines "SGE_RELEASE"
		optimize "On"
