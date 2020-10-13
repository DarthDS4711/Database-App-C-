#ifndef USER_H
#define USER_H
#include <QString>
using namespace std;
class User
{
private:
    QString userName;
    QString email;
    QString password;
public:
    User();
    QString getUserName() const;
    void setUserName(const QString &value);
    QString getEmail() const;
    void setEmail(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
};

#endif // USER_H
