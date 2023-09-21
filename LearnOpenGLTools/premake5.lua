project "LearnOpenGLTools"
kind "StaticLib"
language "C++"
cppdialect "C++17"

files { "**.h", "**.cpp" }
includedirs { "Include", "../Vendor/glad/include", "../Vendor/GLFW/include", "../Vendor/imgui", "../Vendor/imgui/backends", "../Vendor/glm/include" }

links { "glad", "GLFW", "imgui" }