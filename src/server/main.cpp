#include "chatserver.hpp"
#include <iostream>
#include "chatservice.hpp"
#include <signal.h>

using namespace std;

void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char** argv)
{

    if (argc < 3)
    {
        cerr << "command invalid! example: ./ChatServer 127.0.0.1 6000" << endl;
        exit(-1);
    }

    // 解析通过命令行参数传递的ip和port
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);

    signal(SIGINT,resetHandler);  // SIGINT：2 表示终端中断信号

    
    EventLoop loop;
    // 创建一个 InetAddress 对象，指定服务器监听的 IP 地址和端口号
    InetAddress addr(ip, port);
    // 创建一个 ChatServer 实例，传入 EventLoop 对象、监听地址和服务器名称
    ChatServer server(&loop, addr, "GTC-Chat");
    

    server.start();
    loop.loop();

    return 0;
}