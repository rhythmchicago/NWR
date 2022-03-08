--[[
--(C) Copyright 2022 Automated Design Corp. All Rights Reserved.
--File Created: Monday, 7th March 2022 2:06:11 pm
--Author: Thomas C. Bitsky Jr. (support@automateddesign.com)
--]]

workspace "WebView"
    configurations { "Debug", "Release"}

project "WebView"
    kind "WindowedApp"
    language "C"
    toolset "gcc"
    cdialect "gnu11"

    targetdir "bin/%{cfg.buildcfg}"

    files {"src/**.h", "src/**.c", "src/WebView/include/**.h"}
    includedirs { "src/WebView/include" }
    libdirs{ "src/webview/x64"}
    links {"WebView2Guid", "WebView2Loader", "Ole32"}



    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"




    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"


    print("Target dir %{cfg.targetdir}")
    postbuildcommands {
        "copy src/WebView/x64/WebView2Loader.dll %{cfg.targetdir}"
        }