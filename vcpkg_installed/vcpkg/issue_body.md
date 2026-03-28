Package: zlib:x64-windows@1.3.1

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.50.35728.0
- CMake Version: 4.2.3-msvc3
-    vcpkg-tool version: 2025-12-16-44bb3ce006467fc13ba37ca099f64077b8bbf84d
    vcpkg-readonly: true
    vcpkg-scripts version: 544a4c5c297e60e4ac4a5a1810df66748d908869

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Using cached madler-zlib-v1.3.1.tar.gz
-- Extracting source C:/Users/Пользователь/AppData/Local/vcpkg/downloads/madler-zlib-v1.3.1.tar.gz
-- Applying patch 0001-Prevent-invalid-inclusions-when-HAVE_-is-set-to-0.patch
-- Applying patch 0002-build-static-or-shared-not-both.patch
-- Applying patch 0003-android-and-mingw-fixes.patch
-- Using source at C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean
-- Configuring x64-windows
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v
    Working Directory: C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/vcpkg-parallel-configure
    Error code: 1
    See logs for more information:
      C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-dbg-CMakeCache.txt.log
      C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-rel-CMakeCache.txt.log
      C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-dbg-CMakeConfigureLog.yaml.log
      C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-rel-CMakeConfigureLog.yaml.log
      C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-out.log

Call Stack (most recent call first):
  C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_configure.cmake:269 (vcpkg_execute_required_process)
  C:/Users/Пользователь/AppData/Local/vcpkg/registries/git-trees/3f05e04b9aededb96786a911a16193cdb711f0c9/portfile.cmake:17 (vcpkg_cmake_configure)
  scripts/ports.cmake:206 (include)



```

<details><summary>C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-out.log</summary>

```
[1/2] "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E chdir "../../x64-windows-dbg" "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" "C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_INSTALL_PREFIX=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows/debug" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DSKIP_INSTALL_FILES=ON" "-DZLIB_BUILD_EXAMPLES=OFF" "-DCMAKE_MAKE_PROGRAM=C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v145" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg" "-D_VCPKG_INSTALLED_DIR=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed" "-DVCPKG_MANIFEST_INSTALL=OFF" "-DSKIP_INSTALL_HEADERS=ON"
FAILED: [code=1] ../../x64-windows-dbg/CMakeCache.txt 
...
Skipped 14 lines
...

    Change Dir: 'C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-i5ut7n'
    
    Run Build Command(s): C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v cmTC_b62f4
    [1/2] C:\PROGRA~1\MICROS~1\18\COMMUN~1\VC\Tools\MSVC\1450~1.357\bin\Hostx64\x64\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\cmTC_b62f4.dir\testCCompiler.c.obj /FdCMakeFiles\cmTC_b62f4.dir\ /FS -c C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\x64-windows-dbg\CMakeFiles\CMakeScratch\TryCompile-i5ut7n\testCCompiler.c
    FAILED: [code=2] CMakeFiles/cmTC_b62f4.dir/testCCompiler.c.obj 
    C:\PROGRA~1\MICROS~1\18\COMMUN~1\VC\Tools\MSVC\1450~1.357\bin\Hostx64\x64\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\cmTC_b62f4.dir\testCCompiler.c.obj /FdCMakeFiles\cmTC_b62f4.dir\ /FS -c C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\x64-windows-dbg\CMakeFiles\CMakeScratch\TryCompile-i5ut7n\testCCompiler.c
    cl : Command line error D8050 : cannot execute 'C:\PROGRA~1\MICROS~1\18\COMMUN~1\VC\Tools\MSVC\1450~1.357\bin\Hostx64\x64\c1.dll': failed to get command line into debug records
    ninja: build stopped: subcommand failed.
    
    



  CMake will not be able to correctly generate this project.
Call Stack (most recent call first):
  CMakeLists.txt:4 (project)


-- Configuring incomplete, errors occurred!
[2/2] "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E chdir ".." "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" "C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DSKIP_INSTALL_FILES=ON" "-DZLIB_BUILD_EXAMPLES=OFF" "-DCMAKE_MAKE_PROGRAM=C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v145" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg" "-D_VCPKG_INSTALLED_DIR=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed" "-DVCPKG_MANIFEST_INSTALL=OFF"
FAILED: [code=1] ../CMakeCache.txt 
"C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E chdir ".." "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" "C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DSKIP_INSTALL_FILES=ON" "-DZLIB_BUILD_EXAMPLES=OFF" "-DCMAKE_MAKE_PROGRAM=C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v145" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg" "-D_VCPKG_INSTALLED_DIR=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed" "-DVCPKG_MANIFEST_INSTALL=OFF"
-- The C compiler identification is MSVC 19.50.35728.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - failed
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/cl.exe
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/cl.exe - broken
CMake Error at C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeTestCCompiler.cmake:67 (message):
  The C compiler

    "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/cl.exe"

  is not able to compile a simple test program.

  It fails with the following output:

    Change Dir: 'C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-p6ugj2'
    
    Run Build Command(s): C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v cmTC_63f25
    [1/2] C:\PROGRA~1\MICROS~1\18\COMMUN~1\VC\Tools\MSVC\1450~1.357\bin\Hostx64\x64\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\cmTC_63f25.dir\testCCompiler.c.obj /FdCMakeFiles\cmTC_63f25.dir\ /FS -c C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\x64-windows-rel\CMakeFiles\CMakeScratch\TryCompile-p6ugj2\testCCompiler.c
    FAILED: [code=2] CMakeFiles/cmTC_63f25.dir/testCCompiler.c.obj 
    C:\PROGRA~1\MICROS~1\18\COMMUN~1\VC\Tools\MSVC\1450~1.357\bin\Hostx64\x64\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\cmTC_63f25.dir\testCCompiler.c.obj /FdCMakeFiles\cmTC_63f25.dir\ /FS -c C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\x64-windows-rel\CMakeFiles\CMakeScratch\TryCompile-p6ugj2\testCCompiler.c
    cl : Command line error D8050 : cannot execute 'C:\PROGRA~1\MICROS~1\18\COMMUN~1\VC\Tools\MSVC\1450~1.357\bin\Hostx64\x64\c1.dll': failed to get command line into debug records
    ninja: build stopped: subcommand failed.
    
    



  CMake will not be able to correctly generate this project.
Call Stack (most recent call first):
  CMakeLists.txt:4 (project)


-- Configuring incomplete, errors occurred!
ninja: build stopped: subcommand failed.
```
</details>

<details><summary>C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-rel-CMakeCache.txt.log</summary>

```
# This is the CMakeCache file.
# For build in directory: c:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel
# It was generated by CMake: C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
# You can edit this file to change values found and used by cmake.
# If you do not want to change any of the values, simply exit the editor.
# If you do want to change a value, simply edit, save, and exit the editor.
# The syntax for the file is as follows:
# KEY:TYPE=VALUE
# KEY is the name of a variable in the cache.
# TYPE is a hint to GUIs for the type of VALUE, DO NOT EDIT TYPE!.
# VALUE is the current value for the KEY.

########################
# EXTERNAL cache entries
########################

//No help, variable specified on the command line.
BUILD_SHARED_LIBS:UNINITIALIZED=ON

//Path to a program.
CMAKE_AR:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/lib.exe

//Choose the type of build, options are: None Debug Release RelWithDebInfo
// MinSizeRel ...
CMAKE_BUILD_TYPE:STRING=Release

CMAKE_CROSSCOMPILING:STRING=OFF

CMAKE_CXX_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /GR /EHsc /MP '

CMAKE_CXX_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

CMAKE_CXX_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//C compiler
CMAKE_C_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/cl.exe

CMAKE_C_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /MP '

CMAKE_C_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

//Flags used by the C compiler during MINSIZEREL builds.
CMAKE_C_FLAGS_MINSIZEREL:STRING=/O1 /Ob1 /DNDEBUG

CMAKE_C_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//Flags used by the C compiler during RELWITHDEBINFO builds.
CMAKE_C_FLAGS_RELWITHDEBINFO:STRING=/Zi /O2 /Ob1 /DNDEBUG

//Libraries linked by default with all C applications.
CMAKE_C_STANDARD_LIBRARIES:STRING=kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib

//No help, variable specified on the command line.
CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION:UNINITIALIZED=ON

//Flags used by the linker during all build types.
CMAKE_EXE_LINKER_FLAGS:STRING=/machine:x64

//Flags used by the linker during DEBUG builds.
CMAKE_EXE_LINKER_FLAGS_DEBUG:STRING=/nologo    /debug /INCREMENTAL

//Flags used by the linker during MINSIZEREL builds.
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL:STRING=/INCREMENTAL:NO

CMAKE_EXE_LINKER_FLAGS_RELEASE:STRING='/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF  '

//Flags used by the linker during RELWITHDEBINFO builds.
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO:STRING=/debug /INCREMENTAL

//Enable/Disable output of build database during the build.
CMAKE_EXPORT_BUILD_DATABASE:BOOL=

//Enable/Disable output of compile commands during generation.
CMAKE_EXPORT_COMPILE_COMMANDS:BOOL=

//No help, variable specified on the command line.
CMAKE_EXPORT_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY:UNINITIALIZED=ON

//Value Computed by CMake.
CMAKE_FIND_PACKAGE_REDIRECTS_DIR:STATIC=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/pkgRedirects

//No help, variable specified on the command line.
CMAKE_INSTALL_BINDIR:STRING=bin

//No help, variable specified on the command line.
CMAKE_INSTALL_LIBDIR:STRING=lib

//Install path prefix, prepended onto install directories.
CMAKE_INSTALL_PREFIX:PATH=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows

//No help, variable specified on the command line.
CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP:UNINITIALIZED=TRUE

//Path to a program.
CMAKE_LINKER:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/link.exe

//No help, variable specified on the command line.
CMAKE_MAKE_PROGRAM:UNINITIALIZED=C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe

//Flags used by the linker during the creation of modules during
// all build types.
CMAKE_MODULE_LINKER_FLAGS:STRING=/machine:x64

//Flags used by the linker during the creation of modules during
// DEBUG builds.
CMAKE_MODULE_LINKER_FLAGS_DEBUG:STRING=/nologo    /debug /INCREMENTAL

//Flags used by the linker during the creation of modules during
// MINSIZEREL builds.
...
Skipped 157 lines
...

//Use manifest mode, as opposed to classic mode.
VCPKG_MANIFEST_MODE:BOOL=OFF

//No help, variable specified on the command line.
VCPKG_PLATFORM_TOOLSET:UNINITIALIZED=v145

//Appends the vcpkg paths to CMAKE_PREFIX_PATH, CMAKE_LIBRARY_PATH
// and CMAKE_FIND_ROOT_PATH so that vcpkg libraries/packages are
// found after toolchain/system libraries/packages.
VCPKG_PREFER_SYSTEM_LIBS:BOOL=OFF

//Enable the setup of CMAKE_PROGRAM_PATH to vcpkg paths
VCPKG_SETUP_CMAKE_PROGRAM_PATH:BOOL=ON

//No help, variable specified on the command line.
VCPKG_SET_CHARSET_FLAG:UNINITIALIZED=ON

//No help, variable specified on the command line.
VCPKG_TARGET_ARCHITECTURE:UNINITIALIZED=x64

//Vcpkg target triplet (ex. x86-windows)
VCPKG_TARGET_TRIPLET:STRING=x64-windows

//Trace calls to find_package()
VCPKG_TRACE_FIND_PACKAGE:BOOL=OFF

//Enables messages from the VCPKG toolchain for debugging purposes.
VCPKG_VERBOSE:BOOL=OFF

//(experimental) Automatically copy dependencies into the install
// target directory for executables. Requires CMake 3.14.
X_VCPKG_APPLOCAL_DEPS_INSTALL:BOOL=OFF

//(experimental) Add USES_TERMINAL to VCPKG_APPLOCAL_DEPS to force
// serialization.
X_VCPKG_APPLOCAL_DEPS_SERIALIZED:BOOL=OFF

//No help, variable specified on the command line.
ZLIB_BUILD_EXAMPLES:UNINITIALIZED=OFF

//The directory which contains the installed libraries for each
// triplet
_VCPKG_INSTALLED_DIR:PATH=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed

//No help, variable specified on the command line.
_VCPKG_ROOT_DIR:UNINITIALIZED=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg

//Value Computed by CMake
zlib_BINARY_DIR:STATIC=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel

//Value Computed by CMake
zlib_IS_TOP_LEVEL:STATIC=ON

//Value Computed by CMake
zlib_SOURCE_DIR:STATIC=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean


########################
# INTERNAL cache entries
########################

//ADVANCED property for variable: CMAKE_AR
CMAKE_AR-ADVANCED:INTERNAL=1
//This is the directory where this CMakeCache.txt was created
CMAKE_CACHEFILE_DIR:INTERNAL=c:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel
//Major version of cmake used to create the current loaded cache
CMAKE_CACHE_MAJOR_VERSION:INTERNAL=4
//Minor version of cmake used to create the current loaded cache
CMAKE_CACHE_MINOR_VERSION:INTERNAL=2
//Patch version of cmake used to create the current loaded cache
CMAKE_CACHE_PATCH_VERSION:INTERNAL=3
//Path to CMake executable.
CMAKE_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
//Path to cpack program executable.
CMAKE_CPACK_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cpack.exe
//Path to ctest program executable.
CMAKE_CTEST_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/ctest.exe
//ADVANCED property for variable: CMAKE_C_COMPILER
CMAKE_C_COMPILER-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS
CMAKE_C_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_DEBUG
CMAKE_C_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_MINSIZEREL
CMAKE_C_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELEASE
CMAKE_C_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELWITHDEBINFO
CMAKE_C_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_STANDARD_LIBRARIES
CMAKE_C_STANDARD_LIBRARIES-ADVANCED:INTERNAL=1
//Executable file format
CMAKE_EXECUTABLE_FORMAT:INTERNAL=Unknown
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS
CMAKE_EXE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_DEBUG
CMAKE_EXE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELEASE
CMAKE_EXE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_BUILD_DATABASE
CMAKE_EXPORT_BUILD_DATABASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_COMPILE_COMMANDS
CMAKE_EXPORT_COMPILE_COMMANDS-ADVANCED:INTERNAL=1
//Name of external makefile project generator.
CMAKE_EXTRA_GENERATOR:INTERNAL=
//Name of generator.
CMAKE_GENERATOR:INTERNAL=Ninja
//Generator instance identifier.
CMAKE_GENERATOR_INSTANCE:INTERNAL=
//Name of generator platform.
CMAKE_GENERATOR_PLATFORM:INTERNAL=
//Name of generator toolset.
CMAKE_GENERATOR_TOOLSET:INTERNAL=
//Source directory with the top level CMakeLists.txt file for this
// project
CMAKE_HOME_DIRECTORY:INTERNAL=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean
//ADVANCED property for variable: CMAKE_LINKER
CMAKE_LINKER-ADVANCED:INTERNAL=1
//Name of CMakeLists files to read
CMAKE_LIST_FILE_NAME:INTERNAL=CMakeLists.txt
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS
CMAKE_MODULE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_DEBUG
CMAKE_MODULE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL
CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELEASE
CMAKE_MODULE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MT
CMAKE_MT-ADVANCED:INTERNAL=1
//number of local generators
CMAKE_NUMBER_OF_MAKEFILES:INTERNAL=1
//Platform information initialized
CMAKE_PLATFORM_INFO_INITIALIZED:INTERNAL=1
//ADVANCED property for variable: CMAKE_POLICY_VERSION_MINIMUM
CMAKE_POLICY_VERSION_MINIMUM-ADVANCED:INTERNAL=1
//noop for ranlib
CMAKE_RANLIB:INTERNAL=:
//ADVANCED property for variable: CMAKE_RC_COMPILER
CMAKE_RC_COMPILER-ADVANCED:INTERNAL=1
CMAKE_RC_COMPILER_WORKS:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS
CMAKE_RC_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_DEBUG
CMAKE_RC_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_MINSIZEREL
CMAKE_RC_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELEASE
CMAKE_RC_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELWITHDEBINFO
CMAKE_RC_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//Path to CMake installation.
CMAKE_ROOT:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS
CMAKE_SHARED_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_DEBUG
CMAKE_SHARED_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL
CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELEASE
CMAKE_SHARED_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_INSTALL_RPATH
CMAKE_SKIP_INSTALL_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_RPATH
CMAKE_SKIP_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS
CMAKE_STATIC_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_DEBUG
CMAKE_STATIC_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL
CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELEASE
CMAKE_STATIC_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_TOOLCHAIN_FILE
CMAKE_TOOLCHAIN_FILE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_VERBOSE_MAKEFILE
CMAKE_VERBOSE_MAKEFILE-ADVANCED:INTERNAL=1
//Install the dependencies listed in your manifest:
//\n    If this is off, you will have to manually install your dependencies.
//\n    See https://github.com/microsoft/vcpkg/tree/master/docs/specifications/manifests.md
// for more info.
//\n
VCPKG_MANIFEST_INSTALL:INTERNAL=OFF
//ADVANCED property for variable: VCPKG_VERBOSE
VCPKG_VERBOSE-ADVANCED:INTERNAL=1
//Making sure VCPKG_MANIFEST_MODE doesn't change
Z_VCPKG_CHECK_MANIFEST_MODE:INTERNAL=OFF
//Vcpkg root directory
Z_VCPKG_ROOT_DIR:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg

```
</details>

<details><summary>C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-dbg-CMakeCache.txt.log</summary>

```
# This is the CMakeCache file.
# For build in directory: c:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg
# It was generated by CMake: C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
# You can edit this file to change values found and used by cmake.
# If you do not want to change any of the values, simply exit the editor.
# If you do want to change a value, simply edit, save, and exit the editor.
# The syntax for the file is as follows:
# KEY:TYPE=VALUE
# KEY is the name of a variable in the cache.
# TYPE is a hint to GUIs for the type of VALUE, DO NOT EDIT TYPE!.
# VALUE is the current value for the KEY.

########################
# EXTERNAL cache entries
########################

//No help, variable specified on the command line.
BUILD_SHARED_LIBS:UNINITIALIZED=ON

//Path to a program.
CMAKE_AR:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/lib.exe

//Choose the type of build, options are: None Debug Release RelWithDebInfo
// MinSizeRel ...
CMAKE_BUILD_TYPE:STRING=Debug

CMAKE_CROSSCOMPILING:STRING=OFF

CMAKE_CXX_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /GR /EHsc /MP '

CMAKE_CXX_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

CMAKE_CXX_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//C compiler
CMAKE_C_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/cl.exe

CMAKE_C_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /MP '

CMAKE_C_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

//Flags used by the C compiler during MINSIZEREL builds.
CMAKE_C_FLAGS_MINSIZEREL:STRING=/O1 /Ob1 /DNDEBUG

CMAKE_C_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//Flags used by the C compiler during RELWITHDEBINFO builds.
CMAKE_C_FLAGS_RELWITHDEBINFO:STRING=/Zi /O2 /Ob1 /DNDEBUG

//Libraries linked by default with all C applications.
CMAKE_C_STANDARD_LIBRARIES:STRING=kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib

//No help, variable specified on the command line.
CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION:UNINITIALIZED=ON

//Flags used by the linker during all build types.
CMAKE_EXE_LINKER_FLAGS:STRING=/machine:x64

//Flags used by the linker during DEBUG builds.
CMAKE_EXE_LINKER_FLAGS_DEBUG:STRING=/nologo    /debug /INCREMENTAL

//Flags used by the linker during MINSIZEREL builds.
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL:STRING=/INCREMENTAL:NO

CMAKE_EXE_LINKER_FLAGS_RELEASE:STRING='/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF  '

//Flags used by the linker during RELWITHDEBINFO builds.
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO:STRING=/debug /INCREMENTAL

//Enable/Disable output of build database during the build.
CMAKE_EXPORT_BUILD_DATABASE:BOOL=

//Enable/Disable output of compile commands during generation.
CMAKE_EXPORT_COMPILE_COMMANDS:BOOL=

//No help, variable specified on the command line.
CMAKE_EXPORT_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY:UNINITIALIZED=ON

//Value Computed by CMake.
CMAKE_FIND_PACKAGE_REDIRECTS_DIR:STATIC=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/pkgRedirects

//No help, variable specified on the command line.
CMAKE_INSTALL_BINDIR:STRING=bin

//No help, variable specified on the command line.
CMAKE_INSTALL_LIBDIR:STRING=lib

//Install path prefix, prepended onto install directories.
CMAKE_INSTALL_PREFIX:PATH=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows/debug

//No help, variable specified on the command line.
CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP:UNINITIALIZED=TRUE

//Path to a program.
...
Skipped 215 lines
...

//The directory which contains the installed libraries for each
// triplet
_VCPKG_INSTALLED_DIR:PATH=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed

//No help, variable specified on the command line.
_VCPKG_ROOT_DIR:UNINITIALIZED=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg

//Value Computed by CMake
zlib_BINARY_DIR:STATIC=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg

//Value Computed by CMake
zlib_IS_TOP_LEVEL:STATIC=ON

//Value Computed by CMake
zlib_SOURCE_DIR:STATIC=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean


########################
# INTERNAL cache entries
########################

//ADVANCED property for variable: CMAKE_AR
CMAKE_AR-ADVANCED:INTERNAL=1
//This is the directory where this CMakeCache.txt was created
CMAKE_CACHEFILE_DIR:INTERNAL=c:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg
//Major version of cmake used to create the current loaded cache
CMAKE_CACHE_MAJOR_VERSION:INTERNAL=4
//Minor version of cmake used to create the current loaded cache
CMAKE_CACHE_MINOR_VERSION:INTERNAL=2
//Patch version of cmake used to create the current loaded cache
CMAKE_CACHE_PATCH_VERSION:INTERNAL=3
//Path to CMake executable.
CMAKE_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
//Path to cpack program executable.
CMAKE_CPACK_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cpack.exe
//Path to ctest program executable.
CMAKE_CTEST_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/ctest.exe
//ADVANCED property for variable: CMAKE_C_COMPILER
CMAKE_C_COMPILER-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS
CMAKE_C_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_DEBUG
CMAKE_C_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_MINSIZEREL
CMAKE_C_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELEASE
CMAKE_C_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELWITHDEBINFO
CMAKE_C_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_STANDARD_LIBRARIES
CMAKE_C_STANDARD_LIBRARIES-ADVANCED:INTERNAL=1
//Executable file format
CMAKE_EXECUTABLE_FORMAT:INTERNAL=Unknown
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS
CMAKE_EXE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_DEBUG
CMAKE_EXE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELEASE
CMAKE_EXE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_BUILD_DATABASE
CMAKE_EXPORT_BUILD_DATABASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_COMPILE_COMMANDS
CMAKE_EXPORT_COMPILE_COMMANDS-ADVANCED:INTERNAL=1
//Name of external makefile project generator.
CMAKE_EXTRA_GENERATOR:INTERNAL=
//Name of generator.
CMAKE_GENERATOR:INTERNAL=Ninja
//Generator instance identifier.
CMAKE_GENERATOR_INSTANCE:INTERNAL=
//Name of generator platform.
CMAKE_GENERATOR_PLATFORM:INTERNAL=
//Name of generator toolset.
CMAKE_GENERATOR_TOOLSET:INTERNAL=
//Source directory with the top level CMakeLists.txt file for this
// project
CMAKE_HOME_DIRECTORY:INTERNAL=C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/src/v1.3.1-2e5db616bf.clean
//ADVANCED property for variable: CMAKE_LINKER
CMAKE_LINKER-ADVANCED:INTERNAL=1
//Name of CMakeLists files to read
CMAKE_LIST_FILE_NAME:INTERNAL=CMakeLists.txt
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS
CMAKE_MODULE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_DEBUG
CMAKE_MODULE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL
CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELEASE
CMAKE_MODULE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MT
CMAKE_MT-ADVANCED:INTERNAL=1
//number of local generators
CMAKE_NUMBER_OF_MAKEFILES:INTERNAL=1
//Platform information initialized
CMAKE_PLATFORM_INFO_INITIALIZED:INTERNAL=1
//ADVANCED property for variable: CMAKE_POLICY_VERSION_MINIMUM
CMAKE_POLICY_VERSION_MINIMUM-ADVANCED:INTERNAL=1
//noop for ranlib
CMAKE_RANLIB:INTERNAL=:
//ADVANCED property for variable: CMAKE_RC_COMPILER
CMAKE_RC_COMPILER-ADVANCED:INTERNAL=1
CMAKE_RC_COMPILER_WORKS:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS
CMAKE_RC_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_DEBUG
CMAKE_RC_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_MINSIZEREL
CMAKE_RC_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELEASE
CMAKE_RC_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELWITHDEBINFO
CMAKE_RC_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//Path to CMake installation.
CMAKE_ROOT:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS
CMAKE_SHARED_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_DEBUG
CMAKE_SHARED_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL
CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELEASE
CMAKE_SHARED_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_INSTALL_RPATH
CMAKE_SKIP_INSTALL_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_RPATH
CMAKE_SKIP_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS
CMAKE_STATIC_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_DEBUG
CMAKE_STATIC_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL
CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELEASE
CMAKE_STATIC_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_TOOLCHAIN_FILE
CMAKE_TOOLCHAIN_FILE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_VERBOSE_MAKEFILE
CMAKE_VERBOSE_MAKEFILE-ADVANCED:INTERNAL=1
//Install the dependencies listed in your manifest:
//\n    If this is off, you will have to manually install your dependencies.
//\n    See https://github.com/microsoft/vcpkg/tree/master/docs/specifications/manifests.md
// for more info.
//\n
VCPKG_MANIFEST_INSTALL:INTERNAL=OFF
//ADVANCED property for variable: VCPKG_VERBOSE
VCPKG_VERBOSE-ADVANCED:INTERNAL=1
//Making sure VCPKG_MANIFEST_MODE doesn't change
Z_VCPKG_CHECK_MANIFEST_MODE:INTERNAL=OFF
//Vcpkg root directory
Z_VCPKG_ROOT_DIR:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg

```
</details>

<details><summary>C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-rel-CMakeConfigureLog.yaml.log</summary>

```

---
events:
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineSystem.cmake:212 (message)"
      - "CMakeLists.txt:4 (project)"
    message: |
      The system is: Windows - 10.0.26200 - AMD64
  -
    kind: "find-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineCompiler.cmake:63 (find_program)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineCCompiler.cmake:64 (_cmake_find_compiler)"
      - "CMakeLists.txt:4 (project)"
    mode: "program"
    variable: "CMAKE_C_COMPILER"
    description: "C compiler"
    settings:
      SearchFramework: "LAST"
      SearchAppBundle: "LAST"
      CMAKE_FIND_USE_CMAKE_PATH: false
      CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH: false
      CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH: true
      CMAKE_FIND_USE_CMAKE_SYSTEM_PATH: false
      CMAKE_FIND_USE_INSTALL_PREFIX: true
    names:
      - "cc"
      - "gcc"
      - "cl"
      - "bcc"
      - "xlc"
      - "icx"
      - "clang"
    candidate_directories:
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/VC/vcpackages/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TestWindow/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TeamFoundation/Team Explorer/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/Roslyn/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files (x86)/Microsoft SDKs/Windows/v10.0A/bin/NETFX 4.8 Tools/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/FSharp/Tools/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Team Tools/DiagnosticsHub/Collector/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/Extensions/Microsoft/CodeCoverage.Console/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files (x86)/Windows Kits/10/bin/10.0.26100.0/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files (x86)/Windows Kits/10/bin/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/amd64/"
...
Skipped 3478 lines
...
        - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows"
      CMAKE_FIND_ROOT_PATH: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows;C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug"
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineCompilerABI.cmake:83 (try_compile)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:4 (project)"
    checks:
      - "Detecting C compiler ABI info"
    directories:
      source: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-irk2bt"
      binary: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-irk2bt"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: "/machine:x64"
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v145"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_ABI_COMPILED"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-irk2bt'
        
        Run Build Command(s): C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v cmTC_f7dfd
        [1/2] C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_f7dfd.dir\\CMakeCCompilerABI.c.obj /FdCMakeFiles\\cmTC_f7dfd.dir\\ /FS -c "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\Common7\\IDE\\CommonExtensions\\Microsoft\\CMake\\CMake\\share\\cmake-4.2\\Modules\\CMakeCCompilerABI.c"
        FAILED: [code=2] CMakeFiles/cmTC_f7dfd.dir/CMakeCCompilerABI.c.obj 
        C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_f7dfd.dir\\CMakeCCompilerABI.c.obj /FdCMakeFiles\\cmTC_f7dfd.dir\\ /FS -c "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\Common7\\IDE\\CommonExtensions\\Microsoft\\CMake\\CMake\\share\\cmake-4.2\\Modules\\CMakeCCompilerABI.c"
        cl : Command line error D8050 : cannot execute 'C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\c1.dll': failed to get command line into debug records
        ninja: build stopped: subcommand failed.
        
      exitCode: 2
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeTestCCompiler.cmake:56 (try_compile)"
      - "CMakeLists.txt:4 (project)"
    checks:
      - "Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/cl.exe"
    directories:
      source: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-p6ugj2"
      binary: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-p6ugj2"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: "/machine:x64"
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v145"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_COMPILER_WORKS"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-p6ugj2'
        
        Run Build Command(s): C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v cmTC_63f25
        [1/2] C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_63f25.dir\\testCCompiler.c.obj /FdCMakeFiles\\cmTC_63f25.dir\\ /FS -c C:\\Users\\Пользователь\\Desktop\\TestProject\\vcpkg_installed\\vcpkg\\blds\\zlib\\x64-windows-rel\\CMakeFiles\\CMakeScratch\\TryCompile-p6ugj2\\testCCompiler.c
        FAILED: [code=2] CMakeFiles/cmTC_63f25.dir/testCCompiler.c.obj 
        C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_63f25.dir\\testCCompiler.c.obj /FdCMakeFiles\\cmTC_63f25.dir\\ /FS -c C:\\Users\\Пользователь\\Desktop\\TestProject\\vcpkg_installed\\vcpkg\\blds\\zlib\\x64-windows-rel\\CMakeFiles\\CMakeScratch\\TryCompile-p6ugj2\\testCCompiler.c
        cl : Command line error D8050 : cannot execute 'C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\c1.dll': failed to get command line into debug records
        ninja: build stopped: subcommand failed.
        
      exitCode: 2
...
```
</details>

<details><summary>C:\Users\Пользователь\Desktop\TestProject\vcpkg_installed\vcpkg\blds\zlib\config-x64-windows-dbg-CMakeConfigureLog.yaml.log</summary>

```

---
events:
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineSystem.cmake:212 (message)"
      - "CMakeLists.txt:4 (project)"
    message: |
      The system is: Windows - 10.0.26200 - AMD64
  -
    kind: "find-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineCompiler.cmake:63 (find_program)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineCCompiler.cmake:64 (_cmake_find_compiler)"
      - "CMakeLists.txt:4 (project)"
    mode: "program"
    variable: "CMAKE_C_COMPILER"
    description: "C compiler"
    settings:
      SearchFramework: "LAST"
      SearchAppBundle: "LAST"
      CMAKE_FIND_USE_CMAKE_PATH: false
      CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH: false
      CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH: true
      CMAKE_FIND_USE_CMAKE_SYSTEM_PATH: false
      CMAKE_FIND_USE_INSTALL_PREFIX: true
    names:
      - "cc"
      - "gcc"
      - "cl"
      - "bcc"
      - "xlc"
      - "icx"
      - "clang"
    candidate_directories:
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/VC/vcpackages/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TestWindow/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TeamFoundation/Team Explorer/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/Roslyn/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files (x86)/Microsoft SDKs/Windows/v10.0A/bin/NETFX 4.8 Tools/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/FSharp/Tools/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Team Tools/DiagnosticsHub/Collector/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/Extensions/Microsoft/CodeCoverage.Console/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files (x86)/Windows Kits/10/bin/10.0.26100.0/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files (x86)/Windows Kits/10/bin/x64/"
      - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/amd64/"
...
Skipped 3475 lines
...
        - "C:/Program Files"
        - "C:/Program Files (x86)"
        - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake"
        - "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/pkgs/zlib_x64-windows/debug"
      CMAKE_FIND_ROOT_PATH: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows/debug;C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/x64-windows"
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeDetermineCompilerABI.cmake:83 (try_compile)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:4 (project)"
    checks:
      - "Detecting C compiler ABI info"
    directories:
      source: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-selasa"
      binary: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-selasa"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: "/machine:x64"
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v145"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_ABI_COMPILED"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-selasa'
        
        Run Build Command(s): C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v cmTC_5aac4
        [1/2] C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_5aac4.dir\\CMakeCCompilerABI.c.obj /FdCMakeFiles\\cmTC_5aac4.dir\\ /FS -c "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\Common7\\IDE\\CommonExtensions\\Microsoft\\CMake\\CMake\\share\\cmake-4.2\\Modules\\CMakeCCompilerABI.c"
        FAILED: [code=2] CMakeFiles/cmTC_5aac4.dir/CMakeCCompilerABI.c.obj 
        C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_5aac4.dir\\CMakeCCompilerABI.c.obj /FdCMakeFiles\\cmTC_5aac4.dir\\ /FS -c "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\Common7\\IDE\\CommonExtensions\\Microsoft\\CMake\\CMake\\share\\cmake-4.2\\Modules\\CMakeCCompilerABI.c"
        cl : Command line error D8050 : cannot execute 'C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\c1.dll': failed to get command line into debug records
        ninja: build stopped: subcommand failed.
        
      exitCode: 2
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.2/Modules/CMakeTestCCompiler.cmake:56 (try_compile)"
      - "CMakeLists.txt:4 (project)"
    checks:
      - "Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/MSVC/14.50.35717/bin/Hostx64/x64/cl.exe"
    directories:
      source: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-i5ut7n"
      binary: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-i5ut7n"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: "/machine:x64"
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/\u041f\u043e\u043b\u044c\u0437\u043e\u0432\u0430\u0442\u0435\u043b\u044c/Desktop/TestProject/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v145"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_COMPILER_WORKS"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/Пользователь/Desktop/TestProject/vcpkg_installed/vcpkg/blds/zlib/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-i5ut7n'
        
        Run Build Command(s): C:/Users/Пользователь/AppData/Local/vcpkg/downloads/tools/ninja/1.13.1-windows/ninja.exe -v cmTC_b62f4
        [1/2] C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_b62f4.dir\\testCCompiler.c.obj /FdCMakeFiles\\cmTC_b62f4.dir\\ /FS -c C:\\Users\\Пользователь\\Desktop\\TestProject\\vcpkg_installed\\vcpkg\\blds\\zlib\\x64-windows-dbg\\CMakeFiles\\CMakeScratch\\TryCompile-i5ut7n\\testCCompiler.c
        FAILED: [code=2] CMakeFiles/cmTC_b62f4.dir/testCCompiler.c.obj 
        C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\cl.exe  /nologo -D_MBCS  /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -MDd /showIncludes /FoCMakeFiles\\cmTC_b62f4.dir\\testCCompiler.c.obj /FdCMakeFiles\\cmTC_b62f4.dir\\ /FS -c C:\\Users\\Пользователь\\Desktop\\TestProject\\vcpkg_installed\\vcpkg\\blds\\zlib\\x64-windows-dbg\\CMakeFiles\\CMakeScratch\\TryCompile-i5ut7n\\testCCompiler.c
        cl : Command line error D8050 : cannot execute 'C:\\PROGRA~1\\MICROS~1\\18\\COMMUN~1\\VC\\Tools\\MSVC\\1450~1.357\\bin\\Hostx64\\x64\\c1.dll': failed to get command line into debug records
        ninja: build stopped: subcommand failed.
        
      exitCode: 2
...
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "testproject",
  "version": "1.0.0",
  "builtin-baseline": "c27eeddba73f608f10605d80bc0144c1166f8fb7",
  "dependencies": [
    "wxwidgets"
  ]
}

```
</details>
