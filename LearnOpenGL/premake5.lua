project "LearnOpenGL"
kind "ConsoleApp"
language "C++"
cppdialect "C++17"

targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
objdir "obj/%{prj.name}/%{cfg.buildcfg}"

files { "**.cpp" }
includedirs { "../LearnOpenGLTools/Include", "../Vendor/glad/include", "../Vendor/imgui", "../Vendor/glm/include" }

links { "LearnOpenGLTools" }