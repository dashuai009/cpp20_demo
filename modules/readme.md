# modules 模块

这是一种将C++更加现代的代码组织方式。
模块是一组源代码文件，独立于导入它们的翻译单元进行编译。

## 模块试图解决的问题

- 头文件
  - module几乎解决了头文件编译的难题，比如头文件的重复替换
  （复杂项目中，如果一个底层头文件被修改，上层引用的头文件都会被重新编译）。
  使用module之后，这种问题会得到极大的改善。
- 封装：对外接口的暴露
  - 在模块中声明的宏、预处理器指令和未导出的名称在模块外部不可见。
    它们对导入模块的翻译单元的编译没有影响。
    您可以按任意顺序导入模块，而无需考虑宏重定义。导入翻译单元中的声明不参与导入模块中的重载解析或名称查找。
- 编译速度
  - 模块编译一次后，结果将存储在描述所有导出的类型、函数和模板的二进制文件中。
    编译器处理该文件的速度比头文件快得多。
    而且，编译器可以在项目中导入模块的每个位置重用它。

## 实现细节


## 编译器支持状态

## 基本示例

假设我们现在有如下cpp
```c++
int square(int i);// 声明一个函数

class Square {
private:
    int value;
public:
    explicit Square(int i) : value{square(i)} {
    }

    int getValue() const {
        return value;
    }
};

template<typename T>
Square toSquare(const T &x) {
    return Square{x};
}

int square(int i) {// 实现平方函数
    return i * i;
}
```
只需要两步就可以转成一个模块单元：
1. 在第一行添加`export module Square;`，这相当于导出一个名为Square的模块。
2. 把想要导出的函数前面加上export关键字。

```c++
/** modules/mod0/square.ixx **/
export module Square;  // declare module  Square

int square(int i);

export class Square {
private:
    int value;
public:
    explicit Square(int i) : value{square(i)} {
    }

    int getValue() const {
        return value;
    }
};

export template<typename T>
Square toSquare(const T &x) {
    return Square{x};
}

int square(int i) {
    return i * i;
}
```
在主文件中，就可以愉快地`import Square`啦~。
```c++
/*== mod0/main.cpp ==*/
import std;
import Square;  // import module `Square`

int main(){
    Square x = toSquare(42);
    std::cout << x.getValue() << '\n';
}

```

## 我就喜欢写头文件？模块实现单元（module implementation unit）和模块声明单元（module interface unit）

像上边这个例子，属于实现和声明放在一起了，可以写的很pythonic。
模块由若干个模块单元（module units）组成。而且模块可以进行分区（partition），或分为子模块。模块单元是包含模块声明的翻译单元（源文件）。

有几种类型的模块单元：
- 模块接口单元（module interface unit）包含关键词`export module`，
用于导出模块名称和分区（partition）。和.h文件类似。

- 模块实现单元（implementation unit）是不导出模块名称、分区名称。顾名思义，它用于实现模块。和cpp文件类似。

- 主模块接口单元（primary module interface unit）是导出模块名称的模块接口单元。
模块中必须有一个且只能有一个主模块接口单元。上边这个例子里还没有模块分区，直接export module Square，算是主模块单元。

- 模块分区接口单元（partition interface unit）是导出模块分区名称的模块接口单元。

- 模块分区实现单元（partition implementation unit）是模块实现单元，其模块声明中具有模块分区名称，但没有export关键字。

export关键字仅在接口文件中使用。实现文件可以import另一个模块，但不能export任何名称。
实现文件可以具有任何扩展名（这一点编译器还有些特殊处理，好像标准里没有规定）。

## 模块和namespace

不像其它语言，模块不会自动添加一个namespace。
就像第一个例子，import Square之后，Square里导出的所有东西都被直接暴露。
有两种方法可以处理一下，让代码更加规范：

定义一个和模块同名的namespace，
1. 导出命名空间中需要的接口，则命名空间也会被隐式导出，但是命名空间中，没有被导出的接口则不会暴露
```c++
export module Square; // declare module ”Square”
namespace Square {
    int square(int i);// not exported
    export class Square {
        // bala bala ...
    };
    
    export template<typename T>
    Square toSquare(const T& x) {
        // ...
    }
    
    int square(int i) { // not exported
        // ...
    }
}

```
2. 显式导出整个命名空间，则命名空间中的所有声明都会被导出。
```c++
export module Square; // declare module ”Square”

int square(int i);

export namespace Square {
    class Square {
        // ...
    };
    template<typename T>
    Square toSquare(const T& x) {
        // ...
    }
}

int square(int i) { // not exported
    // ...
}
```

这样，在主文件中都可以达到以下效果：
```c++
import Square;// 这个是模块名，需要和export匹配

int main(){
    Square::Square x = Square::toSquare(42);
    // ::前Square是命名空间的名字，::Square是类名，这块搞清楚，之后写模块就简单了
    std::cout << x.getValue() << '\n';
}
```

## 多文件

### 模块接口单元

#### 私有模块片段

### 模块实现单元
### 模块内部（internal）单元

## 模块 和 include

** While in theory modules could replace all traditional header files with all their flaws, in practice this will never happen. **


### global module fragment

现在，我们可以确定，有export module xxx的就是模块接口单元，
没有export关键字，但是有module xxx都是模块实现单元。

c++为了和旧代码兼容(~~为了留住用户~~)，特地兼容了普通的头文件。用到了 全局模块片段(global module fragment)

```c++
module; // start module unit with global module fragment
#include <string>
#include <vector>
export module Mod1; // module declaration

// bula bula bula 
```

前面三行就是全局模块片段，不看前三行，和前面说过的模块单元是一样的。但是
- include进来的 指令 （#define and #include）可以正常 使用和被看到。
- 不会导出任何东西（包括macros, no declarations, no definitions）

### importable header

可被导入的头文件。

比如
```c++
import <vector>;
import "myheader.h";
```

> include头文件和import模块之间的主要区别在于：头文件中的任何预处理器定义在语句之后的导入程序中都可见。

## 其他