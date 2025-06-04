workspace "CrosshairOverlay"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "CrosshairOverlay"

project "CrosshairOverlay"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin-int/%{cfg.buildcfg}")

    -- File sorgenti e header
    files {
        "src/**.cpp",
        "include/**.hpp"
    }

    includedirs {
        "include",
        -- Percorso a vcpkg, aggiorna se necessario
        "$(VCPKG_ROOT)/installed/x64-windows/include"
    }

    libdirs {
        "$(VCPKG_ROOT)/installed/x64-windows/lib"
    }

    links {
        "glfw3",
        "opengl32",
        "imgui"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
