# 要求cmake最低版本
cmake_minimum_required(VERSION 3.0)

# 设置工程名称为 main
project(main)

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)  # 加入调试信息，便于使用 gdb 调试程序。

# 配置头文件搜索路径
# include_directories()

# 配置库文件搜索路径
# link_directories()

# 设置可执行文件的存储路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)  #  定义一个变量 SRC_LIST，包含你需要参与编译的源文件。

# 把.路径下的所有源文件放入SRC_LIST中，避免文件过多，需要一个个列出来
# aux_source_directory(. SRC_LIST)

#  将 SRC_LIST 中的文件编译为一个可执行程序 server 
add_executable(server ${SRC_LIST})

# 目标文件server 需要链接 muduo_net muduo_base pthread 库文件
target_link_libraries(server muduo_net muduo_base pthread)