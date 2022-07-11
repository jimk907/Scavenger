workspace "Scavenger"
	startproject "SgeCreator"
	architecture "x64"

	configurations
	{
		"debug",
		"release"
	}

	tdir = "bin/%{cfg.buildcfg}/%{prj.name}/"
    odir = ".build/%{cfg.buildcfg}/%{prj.name}/"
	ldir = "lib/%{cfg.buildcfg}/"

	tst_tdir = "bin/%{cfg.buildcfg}/tests/%{prj.name}/"
	tst_odir = ".build/%{cfg.buildcfg}/tests/%{prj.name}/"

project "SgeCore"
	location "vs-projects/sgecore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	targetdir(ldir)
    objdir(odir)
	staticruntime "on"
	files
	{
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"include/sgecore/"
	}
	flags
	{
		"FatalWarnings"
	}

project "SgeEngine"
	location "vs-projects/sgeengine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	targetdir(ldir)
    objdir(odir)
	staticruntime "on"
	files
	{
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"include/sgecore/",
		"include/sgeengine/"
	}
	links
	{
		"SgeCore"
	}
	flags
	{
		"FatalWarnings"
	}

project "SgeCreator"
	location "vs-projects/sgecreator"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir(tdir)
    objdir(odir)
	staticruntime "on"
	files
	{
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"include/sgecore/",
		"include/sgeengine/",
		"include/sgecreator/"
	}
	links
	{
		"SgeCore",
		"SgeEngine"
	}
	flags
	{
		"FatalWarnings"
	}

project "Test00_Logger"
	location "vs-projects/tests/test00_logger"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir(tst_tdir)
    objdir(tst_odir)
	staticruntime "on"
	files
	{
		"source/tests/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"include/sgecore/",
		"include/sgeengine/",
		"include/tests/test00_logger/"
	}
	libdirs
	{
		"libs/%{cfg.buildcfg}/"
		
	}
	links
	{
		"SgeCore"
	}
	flags
	{
		"FatalWarnings"
	}

