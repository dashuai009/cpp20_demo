project(modules)


## mod0，先声明模块文件，后生成可执行文件
add_library(modules_lib0)
target_sources(modules_lib0
        PUBLIC
        FILE_SET modules_lib0_files TYPE CXX_MODULES
        FILES mod0/square.ixx)


add_executable(${PROJECT_NAME}_0 mod0/main.cpp)
target_link_libraries(${PROJECT_NAME}_0 modules_lib0 std_ixx)