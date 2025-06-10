#!/bin/bash

# Chatserver 自动编译脚本
# 使用方法：在项目根目录下执行 ./autobuild.sh

# 确保脚本在项目根目录下执行
if [ ! -d "build" ]; then
    echo "错误：未找到 build 目录，当前目录不是项目根目录！"
    exit 1
fi

# 进入 build 目录（已通过前序检查确认存在）
cd build || { echo "错误：无法进入 build 目录（权限不足或目录被删除）"; exit 1; }

# 清理旧构建文件
echo "正在清理旧构建文件..."
rm -rf *

# 生成构建配置
echo "正在生成 CMake 配置..."
cmake ..

# 检查 cmake 是否成功
if [ $? -ne 0 ]; then
    echo "错误：CMake 配置失败！"
    exit 1
fi

# 编译项目
echo "正在编译项目..."
make

# 检查 make 是否成功
if [ $? -ne 0 ]; then
    echo "错误：编译失败！"
    exit 1
fi

echo "🎉 编译成功！可执行文件位于 bin 目录下。"    
