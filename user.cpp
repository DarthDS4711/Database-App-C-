#include "user.h"

QString User::getUserName() const
{
    return userName;
}

void User::setUserName(const QString &value)
{
    userName = value;
}

QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &value)
{
    email = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}

User::User()
{

}
