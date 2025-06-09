#pragma once
#include "user.hpp"

class GroupUser : public User
{
public:
    void setRole(string role) { this->_role = role; }
    string getRole() { return this->_role; }

private:
    string _role;
};