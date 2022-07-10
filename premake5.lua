workspace "Scavenger"
	startproject "SgeCreator"
	architecture "x64"

	configurations
	{
		"debug",
		"release"
	}

	tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
    odir = ".build/%{cfg.buildcfg}/%{prj.name}"
	ldir = "lib/%{cfg.buildcfg}"

	tst_tdir = "bin/%{cfg.buildcfg}/tests/%{prj.name}"
	tst_odir = ".build/%{cfg.buildcfg}/tests/%{prj.name}"

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
		"include/%{prj.name}/**.h",
		"sourec/%{prj.name}/**.h",
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
		"sourec/%{prj.name}/**.h",
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"include/sgecore/",
		"include/sgeengine/"
	}
	links
	{
		"sgecore"
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
		"include/%{prj.name}/**.h",
		"sourec/%{prj.name}/**.h",
		"source/%{prj.name}/**.cpp"
	}
	includedirs
	{
		"include/sgecore/",
		"include/sgeengine/"
	}
	links
	{
		"sgecore",
		"sgeengine"
	}
	flags
	{
		"FatalWarnings"
	}
