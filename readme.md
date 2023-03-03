# cpp20_demo

介绍cpp20

## 编译

目前只有vs 17.5+ preview 可以编译

## clion

把工具链设置为vs preview，cmake 选择`C:\Program Files\Microsoft Visual Studio\2022\Preview\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe`

## vs 17.5preview
https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170

## vs code

需要选择vspreview的工具链（第一次打开项目的时候会选择），设置cmake 的 generator 为ninjia（其他的cmake暂时还不支持）。
vscode的代码提示做的还不太好，推荐clion