workspace "LearnOpenGLv2"
architecture "x64"
configurations { "Debug", "Release" }

-- Dependencies (Static Libraries)
include "Vendor/glad"
include "Vendor/GLFW"
include "Vendor/imgui"
include "LearnOpenGLTools"

-- Projects (Executables)
include "LearnOpenGL"