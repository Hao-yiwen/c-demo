# c-demo

![C11](https://img.shields.io/badge/C-C11-00599C)
![CMake](https://img.shields.io/badge/CMake-3.27%2B-064F8C)
![status](https://img.shields.io/badge/用途-C%20语言复习笔记-informational)

一份 C 语言复习练习。仓库里是几段互相独立的短示例：函数拆到头文件、用指针读写变量，以及一份把这些文件收成静态库的 CMake 配置。它记录学习过程，没有对外接口，也没有第三方依赖。

源文件头注释写于 2024-06-05。

## 内容

| 文件 | 实际内容 |
| --- | --- |
| `file1.h` / `file1.c` | `hello()` 向标准输出打印 `Hello, World!`；`add(int, int)` 返回两数之和。 |
| `file2.c` | 可执行入口。调用 `hello()`，再调用 `add(3, 4)` 并打印结果。 |
| `test.c` | 另一份可执行入口。演示一级指针和二级指针：`value` 为 100，经 `*ptr1` 与 `**ptr2` 读出同一值。三级指针那一行留在注释里。 |
| `library.h` / `library.c` | 再定义了一次 `hello()`。同文件还有 `doStuff(int, unsigned char)`（返回两数之和）和 `increament(int*)`（把指针指向的整数加 1）。头文件只声明了 `hello`。文件后半段是整段注释掉的指针初始化、指针加减和 `ptrdiff_t` 距离示例，其中的 `main` 也在注释里，因此这个文件自己跑不起来。 |
| `CMakeLists.txt` | 要求 CMake 3.27，语言标准 C11。把 `library.c`、`test.c`、`file1.c` 打成静态库 `c_demo`，再用 `file2.c` 生成可执行文件 `c_demo_exec` 并链接该库。 |

`library.c` 里的函数名保持原稿，包括 `increament` 这一拼写。

## 技术栈

- 语言：C11（`CMAKE_C_STANDARD 11`）
- 构建：CMake `cmake_minimum_required(VERSION 3.27)`
- 依赖：仅 C 标准库（`stdio.h`、`stddef.h`），无包管理器、无第三方库

本仓库在以下环境核对过编译结果：

- CMake 3.28.3
- 系统 C 编译器 Clang 18.1.3（`/usr/bin/cc`，CMake 默认使用它）
- GCC 13.3.0（下面两条直接编译命令使用 `gcc`）

## 目录

```text
.
├── CMakeLists.txt    # 静态库 c_demo + 可执行文件 c_demo_exec
├── file1.h           # hello、add 的声明
├── file1.c           # hello、add 的实现
├── file2.c           # 调用 hello 与 add 的 main
├── library.h         # hello 的声明
├── library.c         # hello、doStuff、increament，以及注释掉的指针笔记
├── test.c            # 一、二级指针示例的 main
├── .gitignore        # 忽略 cmake-build-debug/ 与 .idea/
└── README.md
```

`.gitignore` 忽略 CLion 的 `cmake-build-debug/` 和 `.idea/`，仓库根目录没有提交构建产物。

## 环境要求

- 支持 C11 的 C 编译器（GCC 或 Clang）
- 若走仓库里的 CMake 工程：CMake 3.27 或更高版本

## 运行

下面两组命令只编译当前能独立运行的示例，已在上述环境执行并通过。

打印问候和加法结果（`file1.c` + `file2.c`）：

```bash
gcc -std=c11 file1.c file2.c -o c_demo_exec
./c_demo_exec
```

```text
Hello, World!
Result of add: 7
```

打印指针解引用（`test.c` 自带 `main`，不要和 `file2.c` 一起链接）：

```bash
gcc -std=c11 test.c -o test_pointers
./test_pointers
```

```text
There are 3 apples
Value = 100
Value using ptr1 = 100
Value using ptr2 = 100
```

`library.c` 可以单独编译成目标文件，没有可用的 `main`：

```bash
gcc -std=c11 -c library.c -o library.o
```

### CMake

按仓库里的 `CMakeLists.txt` 配置并构建：

```bash
cmake -S . -B build
cmake --build build
```

在 CMake 3.28.3、Clang 18.1.3 下，静态库 `build/libc_demo.a` 能生成，链接 `c_demo_exec` 失败，链接器报告：

```text
multiple definition of `hello'
```

`hello` 在 `library.c` 和 `file1.c` 里各有一份定义，而 `file2.c` 同时用到 `hello` 和只在 `file1.c` 里实现的 `add`，链接静态库时两份目标文件都会被拉进来。

`test.c` 和 `file2.c` 还各自有一个 `main`。这次报错停在重复的 `hello`，链接器没有继续报告 `main`。`test.c` 放在静态库里，当前可执行文件没有引用它独有的符号，所以这一次没有把它链进去。

因此现在能运行的是上面两条 `gcc` 命令。CMake 目标要能链过，需要先处理重复的 `hello`（以及库内 `test.c` 自带的 `main`）。本仓库按学习笔记原样保留这些源文件，文档不改业务代码。

## 参考

- 构建入口：`CMakeLists.txt`
- 标准：C11，由 `CMAKE_C_STANDARD` 指定；直接编译时请带上 `-std=c11`
