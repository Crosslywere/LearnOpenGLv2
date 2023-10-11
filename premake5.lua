workspace "LearnOpenGLv2"
architecture "x64"
configurations { "Debug" }

-- Dependencies (Static Libraries)
include "Vendor/glad"
include "Vendor/GLFW"
include "Vendor/imgui"
include "Vendor/stb"
include "LearnOpenGLTools"

-- Projects (Executables)
include "LearnOpenGL"