cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API  "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
# set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
project(cpp20_demo)

#include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)
# turn on the dynamic depends for ninja
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

if (MSVC)
    #add_compile_options(/W4 /WX)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.34")
        string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
                "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> <SOURCE> -nologo -TP"
                " -showIncludes"
                " -scanDependencies <DYNDEP_FILE>"
                " -Fo<OBJECT>")
        message("${CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE}")
        set(CMAKE_EXPERIMENTAL_CXX_SCANDEP_DEPFILE_FORMAT "msvc")
        set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "msvc")
        set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG "@<MODULE_MAP_FILE>")
    endif ()
else ()
    #add_compile_options(-Wall -Werror -Wstrict-prototypes -Wmissing-prototypes)
endif ()


#set(VCToolsInstallDir "C:/Program Files/Microsoft Visual Studio/2022/Preview/VC/Tools/MSVC/14.36.32323/modules/std.ixx")
# 添加std的模块支持。需要从上边这个目录里复制std.ixx过来。
# vs 17.5 preview 开始支持，需要安装组件：适用于v143生成工具的c++模块（x64/x86-实验性）
# https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170

add_library(std_ixx)
target_sources(std_ixx
        PUBLIC
        FILE_SET std_ixx_all TYPE CXX_MODULES
        FILES std.ixx)

# fmt
#FetchContent_Declare(fmt
#        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#        GIT_TAG master
#        )
#FetchContent_MakeAvailable(fmt)
#find_package(fmt)

#
#add_subdirectory(utils)
#
#add_library(tmp)
#target_sources(tmp
#        PUBLIC
#        FILE_SET tmp_all TYPE CXX_MODULES
#        FILES tmp/max_value.ixx tmp/push_back.ixx tmp/my_fmt.ixx tmp/ranges.ixx)
#target_link_libraries(tmp std_ixx)

add_executable(main main.cpp)
target_link_libraries(main std_ixx)

##
#  https://www.kitware.com/import-cmake-c20-modules/
# VCToolsInstallDir  std.ixx要复制过来
# 裸漏的ixx文件，不能直接add进去，要通过target_sources添加进FILE_SET