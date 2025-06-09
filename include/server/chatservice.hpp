#pragma once

#include <unordered_map>
#include <iostream>
#include <muduo/net/TcpConnection.h>
#include <functional>
#include <json.hpp>
#include "usermodel.hpp"
#include <mutex>
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"
using namespace std;
using namespace muduo::net;
using namespace muduo;

using json = nlohmann::json;
using MsgHandler = std::function<void(const TcpConnectionPtr& conn, json& js, Timestamp)>;

class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService* instance();

    // 处理登录业务
    void login(const TcpConnectionPtr& conn, json& js, Timestamp time);

    // 处理注册业务
    void reg(const TcpConnectionPtr& conn, json& js, Timestamp time);

    // 一对一聊天服务
    void oneChat(const TcpConnectionPtr& conn, json& js, Timestamp time);

    // 添加好友业务
    void addFriend(const TcpConnectionPtr& conn, json& js, Timestamp time);

    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

    // 处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr& conn);

    // 服务器异常，业务重置方法
    void reset();

    // 创建群组
    void createGroup(const TcpConnectionPtr& conn, json& js, Timestamp time);

    // 加入群组
    void addGroup(const TcpConnectionPtr& conn, json& js, Timestamp time);

    // 群聊天
    void groupChat(const TcpConnectionPtr& conn, json& js, Timestamp time);
    
    // 注销
    void loginout(const TcpConnectionPtr& conn, json& js, Timestamp time);

    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int userid, string msg);

private:
    ChatService();
    
    // 存储消息id和其对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 数据操作类对象
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;
    
    // 存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap; 

    // 定义互斥锁，保证线程安全
    mutex _connMutex;

    // 定义redis对象
    Redis _redis;
}; 
