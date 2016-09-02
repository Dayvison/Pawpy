solution "pawnpy"
	configurations { "Release", "Debug" }
	language "C++"
	flags { "C++14"}

	project "pawnpy"
		includedirs { "sdk"}
		kind "SharedLib"
		if _ACTION == "gmake" then
			files { "**.cpp" }
			links "rt"
			targetextension ".so"
		elseif string.startswith(_ACTION, "vs") then
			files { "**.cpp", "**.def" }
			targetextension ".dll"
		end

	configuration "Release"
		if _ACTION == "gmake" then
			defines {"LINUX"}
			buildoptions { "-fno-strict-aliasing", "-fPIC", "-m32", "-O3", "-Wall"}
			linkoptions {"-m32", "`python2.7-config --ldflags`"}
			flags "NoImportLib"
			objdir "build/obj/linux/Release"
			targetdir "build/bin/linux/Release"
		elseif string.startswith(_ACTION, "vs") then
			flags { "FatalWarnings", "LinkTimeOptimization", "NoBufferSecurityCheck" }
			optimize "Speed"
			objdir "build/obj/win32/Release"
			targetdir "build/bin/win32/Release"
		end

	configuration "Debug"
		if _ACTION == "gmake" then
			defines {"LINUX"}
			buildoptions { "-fPIC", "-m32", "-O0", "-Wall" }
			linkoptions { "-m32", "-rdynamic", "`python2.7-config --ldflags`"}
			flags { "NoImportLib", "Symbols" }
			objdir "build/obj/linux/Debug"
			targetdir "build/bin/linux/Debug"
		elseif string.startswith(_ACTION, "vs") then
			defines {"LINUX"}
			flags { "FatalWarnings", "Symbols" }
			objdir "build/obj/win32/Debug"
			targetdir "build/bin/win32/Debug"
		end