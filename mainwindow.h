#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <regex>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <algorithm>
#include <QDebug>
#include <QPalette>
#include <QHBoxLayout>
#include <QGridLayout>
#include <memory.h>
#include "user.h"
#include "productwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_usernameLE_textChanged(const QString &arg1);

    void on_paswordLE_textChanged(const QString &arg1);

    void on_newUserLE_textChanged(const QString &arg1);

    void on_emailLE_textChanged(const QString &arg1);

    void on_newPasswordLE_textChanged(const QString &arg1);

    void on_signInPB_clicked();

    void on_loginPB_clicked();

    void openFile();

    void on_comboBox_currentIndexChanged(int index);

private:
    //part of variables of the program
    Ui::MainWindow *ui;
    vector<User> users;
    vector<Product>products;
    QGridLayout *gLay;
    QAction *openFileAction;
    QFile dbFile;
    QJsonArray dbArray;
    QJsonObject dbJson;
    //Block of methods
    void enableLoginPB();
    void enableSignInPB();
    void validateUser();
    bool validateEmail(const QString &email);
    void saveDB();
    void loadDB();
    void sortByUserID();
    void sortByEmail();
    void sortProducts();
    int validateNewUser(const QString &userID, const QString &userEmail);
    int validateNewUserByEmail(const QString &userEmail);
    int findFirstProduct(const QString &firstId);
    void addWidget();
    void deleteWidgets();
    void createListProducts(int index, const QString & prefix);
    void addWidgets(vector<Product> &list);
    //Block of enums
    enum viewsAPP{
        mainWindow = 1
    };
    //Block of structs
    struct sortUserID{
        bool operator()(User &u1, User &u2){
            return  u1.getUserName() < u2.getUserName();
        }
    } myObject;
    struct sortEmail{
        bool operator()(User &u1, User &u2){
            return  u1.getEmail() < u2.getEmail();
        }
    } myObject1;
    struct sortProducts{
        bool operator()(Product &p1, Product &p2){
            return p1.getId() < p2.getId();
        }
    }condition;
};

#endif // MAINWINDOW_H
