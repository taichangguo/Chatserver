#include <iostream>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <functional>
#include <string>
using namespace std;
using namespace muduo::net;
using namespace std::placeholders;

/* 基于muduo网络库开发服务器程序
1. 组合TcpServer对象
2. 创建EventLoop事件循环对象的指针
3. 明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
4. 在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
5. 设置合适的服务端线程数量，muduo库会自己分配I/O线程和worker线程
*/

class ChatServer
{
public:
    ChatServer(EventLoop *loop,               // 事件循环
               const InetAddress &listenAddr, // IP+Port
               const string &nameArg)         // 服务器的名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 注册用户连接回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); // bind 是模板函数，必须显式用 std::bind

        // 注册读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置线程数量（1 I/O + 3 worker）
        _server.setThreadNum(4);
    }

    // 开启事件循环
    void start()
    {
        _server.start();
    }

private:

    // 专门处理用户的连接，创建和断开
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << "-->" << conn->localAddress().toIpPort() << " 建立连接" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << "-->" << conn->localAddress().toIpPort() << " 连接断开" << endl;
            conn->shutdown();
        }
    }

    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn, // 连接
                   Buffer *buffer,               // 缓冲区
                   muduo::Timestamp time)        // 时间信息
    {
        string msg = buffer->retrieveAllAsString();
        cout << "recv data: " << msg << " | time: " << time.toFormattedString() << endl;
        conn->send(msg);
    }

    TcpServer _server;
    EventLoop *_loop;
};

int main()
{
    EventLoop loop; // epoll
    InetAddress addr("127.0.0.1", 6000);    // 设置服务器监听的本地地址（IP+端口）
    ChatServer server(&loop, addr, "ChatServer");  // 创建一个聊天服务器对象，绑定地址和事件循环。
    server.start();
    loop.loop();  // epoll_wait 以阻塞方式等待新用户连接，已连接用户的读写事件等

}