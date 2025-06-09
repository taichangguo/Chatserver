#pragma once
#include "user.hpp"

// 用户表数据操作类
class UserModel {
public:
    // 插入用户信息（注册功能）
    bool insert(User &user);

    // 根据用户号码查询用户信息
    User query(int id);

    // 更新用户的状态信息
    bool updateState(User user);

    // 重置用户的状态信息
    void resetState();
}; 