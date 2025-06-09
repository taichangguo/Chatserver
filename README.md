chatserver
可以工作在 Nginx TCP 负载均衡环境 中的集群聊天服务器和客户端源码，基于 muduo 库实现。
编译方式
进入构建目录：
bash
cd build  

清理旧构建文件（谨慎操作，会删除 build 内所有文件）：
bash
rm -rf *  


生成构建配置（关联项目根目录的 CMakeLists.txt）：
bash
cmake ..  


编译项目：
bash
make
