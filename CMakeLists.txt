cmake_minimum_required(VERSION 3.10)
project(MP157Test)

#set(CMAKE_SYSTEM_NAME Linux)  # 指定目标系统名称
#set(CMAKE_SYSTEM_PROCESSOR arm)  # 指定目标处理器类型

#set(CMAKE_C_COMPILER "/usr/local/arm/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-gcc")  # 指定交叉编译器路径
#set(CMAKE_CXX_COMPILER "/usr/local/arm/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-g++")  # 指定交叉C++编译器路径


# 其他设置...

#set(CMAKE_FIND_ROOT_PATH "/usr/local/arm/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf")  # 指定目标系统根目录路径
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)  # 不在目标系统根目录下查找程序
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)  # 仅在目标系统根目录下查找库
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)  # 仅在目标系统根目录下查找头文件


# 设置构建输出目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)

# 添加子目录
add_subdirectory(Module/utils)
add_subdirectory(Module/startup)


# 编译主程序
add_executable(MP157Test src/app_main.c)

# 头文件路径
target_include_directories(MP157Test PUBLIC include/sys)
target_include_directories(MP157Test PUBLIC include/logger)
target_include_directories(MP157Test PUBLIC include/queue)

add_custom_target(CopyFile
    COMMAND echo "Copy file to remote"
    COMMAND scp build/bin/MP157Test  root@192.168.7.1:/home/root
)

# 链接模块
target_link_libraries(MP157Test utils startup)
