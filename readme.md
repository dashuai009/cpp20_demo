# cpp20_demo

介绍cpp20

> 编译标准是c++23，主要是因为用的std模块的特性，泰忒么好用了，其他主要是c++20的特性。
## 组织结构


每个文件夹对应一个章节。本项目的根目录下的cmakelists.txt会挨个add_subdirectory，不想看哪个注释掉就好。

推荐以下顺序阅读：

- `modules` c++20的模块特性，开天辟地，从这开始

## 编译

目前只有vs 17.5+ preview 可以编译

## clion

把工具链设置为vs preview，cmake 选择`C:\Program Files\Microsoft Visual Studio\2022\Preview\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe`

## vs 17.5preview
https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170

## vs code

需要选择vspreview的工具链（第一次打开项目的时候会选择），设置cmake 的 generator 为ninjia（其他的cmake暂时还不支持）。
vscode的代码提示做的还不太好，推荐clion