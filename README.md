Scavenger Game Engine

This project is a work in progress and utilizes numerous ideas "scavenged" from multiple sources and adapted for use with this project. Some of the sources (original authors) of these scavenged code snippets are lost but sources will be cited in the code base when known.

Design Criteria:

This code will target the Windows operating system although some allowance may be made to facilitate future development on other OS platforms such as Linux and Mac. Initially, the rendering platform will be built upon Opengl but future support for Vulkan (for sure) and DirectX (possibly) renderers will be provided. As much as is practical, all code will be written from scratch but some third party dependencies will exist. For example, the math library is custom. The Window class is custom and as a result does not play nicely with some popular external libraries such as IMGUI, but if IMGUI is eventually utilized, it will be modified to work with the Scavenger window class.

There will be at least three primary static libraries providing the game engine services to support games and applications. SgeCore.lib will contain various classes and functions for support of the engine and applications/games. For example, it will include the math, file and string utilities, etc. SgeEngine.lib will contain classes and code which will serve as the base for games and application and include various services and base-classes for creating and managing applications to run the platform. A third library, SgeTest.lib will define functions and classes to support software testing. This library is totally custom and will be linked as needed for specific code testing applications.

Scavenger will also include a suite of applications such as SgeCreator.exe for creating game content and SgeLoader.exe for loading and launching games.

Note:

Initially, there will be copious use of code practices that many consider "bad". For example, raw pointers, global variables or functions, compiler macros which are specific to certain development platforms, and there may or may not be singleton-like design patterns. For the most part this is due to the fact this code is developed by a one-person "team". Me, and I have developed certain standards which tolerate some of less-than ideal design principles. Eventually this will likely be corrected but  the main goal right now is develop something that works and deal with details later.

Final Word:

Right now I am a github noob. This is my first public code repository and I barely understand the proper usage and language of github. I hope to be developing github proficiency as I progress.
