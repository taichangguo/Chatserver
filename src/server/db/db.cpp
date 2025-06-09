#include <db.h>
#include <muduo/base/Logging.h>

using namespace muduo;

// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";


MySQL::MySQL()
{
    // 调用 mysql_init 函数初始化一个新的 MySQL 连接句柄
    // 传入 nullptr 表示使用默认的初始化选项
    // 初始化后的句柄将存储在成员变量 _conn 中
    _conn = mysql_init(nullptr);
}

// 释放数据库连接资源
MySQL::~MySQL()
{
    if (_conn != nullptr)
    {
        // 若连接句柄有效，调用 mysql_close 函数关闭 MySQL 连接
        // 释放连接占用的系统资源
        mysql_close(_conn);
    }
}

// 连接数据库
bool MySQL::connect()
{
    MYSQL *p = mysql_real_connect(
        _conn, 
        server.c_str(), 
        user.c_str(), 
        password.c_str(), 
        dbname.c_str(), 
        3306, 
        nullptr, 
        0
    );
    if (p != nullptr)
    {
        // 设置字符集为GBK（解决中文乱码）
        // mysql_query(_conn, "set names gbk");
        mysql_query(_conn, "set names utf8mb4");

        LOG_INFO << "connect mysql success!";
    }
    else
    {
        LOG_INFO << "connect mysql error!";
    }
    // 连接成功返回非空指针，转换为 true；失败返回 nullptr，转换为 false
    return p; 
}

// 更新操作（插入、删除、修改）
bool MySQL::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        // 日志输出错误信息（__FILE__/__LINE__是编译器内置宏）
        // 分别表示当前文件名和当前代码所在行号，方便定位问题
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" 
                    << sql << "更新失败!";
        return false;
    }
    return true; 
}

// 查询操作
MYSQL_RES* MySQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" 
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

// 
MYSQL* MySQL::getConnection()
{
    return _conn;
}