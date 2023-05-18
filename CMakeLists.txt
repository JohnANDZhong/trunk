cmake_minimum_required(VERSION 3.10)
project(MP157Test)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置构建输出目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)

# 添加子目录
add_subdirectory(Module/utils)


# 编译主程序
add_executable(MP157Test src/main.c)

# 头文件路径
target_include_directories(MP157Test PUBLIC include/utils)


# 链接模块
target_link_libraries(MP157Test utils)
