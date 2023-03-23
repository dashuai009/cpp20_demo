project(modules)


## mod0，先声明模块文件，后生成可执行文件
add_library(modules_lib0)
target_sources(modules_lib0
        PUBLIC
        FILE_SET modules_lib0_files TYPE CXX_MODULES
        FILES mod0/square.ixx)


add_executable(${PROJECT_NAME}_0 mod0/main.cpp)
target_link_libraries(${PROJECT_NAME}_0 modules_lib0 std_ixx)



## mod1，先声明模块文件，后生成可执行文件
# 现在不可编译
#add_library(modules_lib1)
#target_sources(modules_lib1
#        PUBLIC
#        FILE_SET modules_lib1_files TYPE CXX_MODULES
#        FILES mod1/mod1.ixx mod1/mod1io.ixx mod1/mod1price.ixx)
#target_link_libraries(modules_lib1 std_ixx)
#
#add_executable(${PROJECT_NAME}_1 mod1/main.cpp)
#target_link_libraries(${PROJECT_NAME}_1 modules_lib1 std_ixx)



## mod2，先声明模块文件，后生成可执行文件
add_library(modules_lib2)
target_sources(modules_lib2
        PUBLIC
        FILE_SET modules_lib2_files TYPE CXX_MODULES
        FILES mod2/mod2.ixx mod2/mod2order.ixx mod2/mod2price.ixx)
target_link_libraries(modules_lib2 std_ixx)

add_executable(${PROJECT_NAME}_2 mod2/main.cpp)
target_link_libraries(${PROJECT_NAME}_2 modules_lib2 std_ixx)

## mod3，先声明模块文件，后生成可执行文件
# 现在不可编译
#add_library(modules_lib3)
#target_sources(modules_lib3
#        PUBLIC
#        FILE_SET modules_lib3_files TYPE CXX_MODULES
#        FILES mod3/mod3.cppm mod3/mod3customer.cppm mod3/mod3io.cpp mod3/mod3price.cpp)
#
#add_executable(${PROJECT_NAME}_3 mod3/testmod3.cpp)
#target_link_libraries(${PROJECT_NAME}_3 modules_lib)