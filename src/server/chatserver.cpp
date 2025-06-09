#include "chatserver.hpp"
#include <functional>
#include "json.hpp"
#include "chatservice.hpp"
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    // 使用初始化列表初始化 _server 和 _loop 成员变量
    : _server(loop, listenAddr, nameArg), _loop(loop) 
{
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); // bind 是模板函数，必须显式用 std::bind

    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    _server.setThreadNum(4);
}


void ChatServer::start()
{
    _server.start();
}


void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
     // 检查连接状态，若连接已断开
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();   // 调用 shutdown 方法关闭连接，释放相关资源
    }
}

void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           muduo::Timestamp time)
{
    // 从缓冲区中取出所有数据，并将其转换为字符串
    string buf = buffer->retrieveAllAsString();
    // 将获取到的字符串解析为 JSON 对象
    json js = json::parse(buf);
    //通过msgid获取业务处理器
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn, js, time);
}