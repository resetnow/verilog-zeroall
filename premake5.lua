local pli_include_path = os.getenv("PLI_INCLUDE_PATH")
local pli_library_path = os.getenv("PLI_LIBRARY_PATH")
local pli_library = os.getenv("PLI_LIBRARY")
local gcc_prefix = os.getenv("GCC_PREFIX")

workspace "verilog-zeroall"
   configurations { "Release" }

project "verilog-zeroall"
   kind "SharedLib"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   gccprefix (gcc_prefix)

   files { "src/**.h", "src/**.c" }
   includedirs { (pli_include_path) }
   libdirs { (pli_library_path) }
   links { (pli_library) }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"