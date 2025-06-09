#pragma once
#include <string>

using namespace std;

class User {

protected:
    int id;               // 对应数据库表中的id字段（主键自增）
    string name;          // 对应数据库表中的name字段（用户名）
    string password;      // 对应数据库表中的password字段（密码）
    string state;         // 对应数据库表中的state字段（用户状态，默认offline）

public:
    // 构造函数（带默认值）
    User(int id = -1, string name = "", string password = "", string state = "offline")
        : id(id), name(name), password(password), state(state) {}

    // Get 方法
    int getId() const { return id; }
    string getName() const { return name; }
    string getPwd() const { return password; }
    string getState() const { return state; }
    

    // Set 方法
    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setPwd(string password) { this->password = password; }
    void setState(string state) { this->state = state; }
};
