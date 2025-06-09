#pragma once

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace std;
using namespace muduo::net;

// 聊天服务器的主类
class ChatServer
{
public:
    // 初始化聊天服务器对象
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg);

    // 启动
    void start();

private:
    // 专门处理用户的连接，创建和断开
    void onConnection(const TcpConnectionPtr &conn);

    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn, // 连接
                   Buffer *buffer,               // 缓冲区
                   muduo::Timestamp time);       // 时间信息
    TcpServer _server;
    EventLoop *_loop;
};