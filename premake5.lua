workspace "LearnOpenGLv2"
architecture "x64"
configurations { "Debug", "Release" }

-- Dependencies (Static Libraries)
include "Vendor/GLFW"
include "Vendor/glad"
include "LearnOpenGLTools"

-- Projects (Executables)
include "LearnOpenGL"