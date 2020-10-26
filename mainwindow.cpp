#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qlabel.h"
#include <QBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFileAction = new QAction("Open Database", this);
    //quien envia el mensaje o la señal, que señal esta enviado, quien responderá, con que slot responderá
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    ui->menuBar->addMenu("&File")->addAction(openFileAction);
    gLay = new QGridLayout(this);
//    dbFile.setFileName("lerma.json");
//    dbFile.open(QIODevice::WriteOnly);
//    dbFile.close();

}

MainWindow::~MainWindow()
{
    saveDB();
    delete ui;
}

void MainWindow::enableLoginPB()
{
    int longTextUser = ui->usernameLE->text().length();
    int longTextPassword = ui->paswordLE->text().length();
    if((longTextUser > 0 ) && longTextPassword > 0){
        ui->loginPB->setEnabled(true);
    }
    else{
        ui->loginPB->setEnabled(false);
    }
}

void MainWindow::enableSignInPB()
{
    int longTextNewUser = ui->newUserLE->text().length();
    int longTextEmail = ui->emailLE->text().length();
    int longTextNewPassword = ui->newPasswordLE->text().length();
    if((longTextNewUser > 0) && longTextEmail > 0 && longTextNewPassword > 0){
        ui->signInPB->setEnabled(true);
    }
    else{
        ui->signInPB->setEnabled(false);
    }
}

void MainWindow::validateUser()
{
    QMessageBox message;
    vector<User>::iterator it;
    QString user = ui->usernameLE->text();
    QString password = ui->paswordLE->text();
    it = find_if(users.begin(), users.end(), [&user, &password](User u) ->bool {
        return u.getPassword() == password && u.getUserName() == user;
    });

    if(it == users.end()){
        message.setText("Invalid credentials for the user");
        message.setIcon(QMessageBox::Warning);
        message.exec();
    }
    else{
        message.setText("Welcome to LERMA user: " + user);
        message.setIcon(QMessageBox::Information);
        ui->viewSW->setCurrentIndex(mainWindow);
        addWidget();
        message.exec();
    }
}

bool MainWindow::validateEmail(const QString &email)
{
    string emailToValidate = email.toStdString();
    regex val("(\\w+)(\\.|_)?(\\w+)?@(\\w+)(\\.(\\w+))+");
    bool match = regex_match(emailToValidate, val);
    return match;
}

void MainWindow::saveDB()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    jsonObj = dbJson;
    jsonDoc = QJsonDocument(jsonObj);
    dbFile.open(QIODevice::WriteOnly);
    dbFile.write(jsonDoc.toJson());
    dbFile.close();


}

void MainWindow::loadDB()
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    if(dbFile.open(QIODevice::ReadOnly)){
        QByteArray data = dbFile.readAll();
        dbFile.close();
        qDebug() << data.size();
        jsonDoc = QJsonDocument::fromJson(data);
        jsonObj = jsonDoc.object();
        dbArray = jsonObj["products"].toArray();
        for(int i(0); i < dbArray.size(); ++i){
            Product p;
            QJsonObject obj = dbArray[i].toObject();
            p.setId(obj["id"].toString());
            p.setNameProduct(obj["name"].toString());
            p.setPriceProduct(obj["price"].toDouble());
            products.push_back(p);
            qDebug() << p.getNameProduct() << endl;
        }
        dbArray = jsonObj["users"].toArray();
        for(int i(0); i < dbArray.size(); ++i){
            User u;
            QJsonObject obj = dbArray[i].toObject();
            u.setUserName(obj["name"].toString());
            u.setEmail(obj["email"].toString());
            u.setPassword(obj["password"].toString());
            users.push_back(u);
            qDebug() << u.getUserName() << endl;
        }
        dbJson = jsonDoc.object();
        sortProducts();
    }
    else{
        QMessageBox message;
        message.setText("Hubo un error al abrir el archivo");
        message.setIcon(QMessageBox::Critical);
        message.exec();
        return;
    }
}

void MainWindow::sortByUserID()
{
    sort(users.begin(), users.end(), myObject);
}

void MainWindow::sortByEmail()
{
    sort(users.begin(), users.end(), myObject1);
}

void MainWindow::sortProducts()
{
    sort(products.begin(), products.end(), condition);
}

int MainWindow::validateNewUser(const QString &userID, const QString &userEmail)
{
    int factor = 0;
    sortByUserID();
    int l = 0;
    int r = users.size() - 1;
    int m;
    while(l <= r){
        m = (l + r) / 2;
        User u = users[m];
        QString id = u.getUserName();
        if(id == userID){
            factor = -1;
            break;
        }
        else if(id < userID)
            l = m + 1;
        else if(id > userID)
            r = m - 1;
    }
    if(l > r)
        factor = 1;
    if(factor == -1)
        return -2;
    else{
        int factor2 = validateNewUserByEmail(userEmail);
        return factor + factor2;

    }
}

int MainWindow::validateNewUserByEmail(const QString &userEmail)
{
    int factor = 0;
    sortByEmail();
    int l = 0;
    int r = users.size() - 1;
    int m;
    while(l <= r){
        m = (l + r) / 2;
        User u = users[m];
        QString email = u.getEmail();
        if(email == userEmail){
            factor = -1;
            break;
        }
        else if(email < userEmail)
            l = m + 1;
        else if(email > userEmail)
            r = m - 1;
    }
    if(l > r)
        factor = 1;
    return factor;
}

int MainWindow::findFirstProduct(const QString &firstId)
{
    sortProducts();
    int index = -1;
    int l = 0;
    int r = products.size() - 1;
    int m;
    while(l <= r){
        m = (l + r) / 2;
        Product p = products[m];
        QString id = p.getId();
        if(id == firstId){
            index = m;
            break;
        }
        else if(id < firstId)
            l = m + 1;
        else if(id > firstId)
            r = m - 1;
    }
    return index;
}

void MainWindow::addWidget()
{
    size_t index = 0;
    int i = 0;
    int j = 0;
    bool stateAdd = true;
    while(stateAdd){
        if(j < 4){
            ProductWidget * product = new ProductWidget();
            product->setFixedSize(200, 300);
            product->addInformation(products[index++]);
            gLay->addWidget(product, i, j);
            j++;
        }
        else if(j >= 4){
            i++;
            j = 0;
        }
        if(index >= products.size())
            stateAdd = false;

    }
    ui->scrollContent->setLayout(gLay);
}

void MainWindow::deleteWidgets()
{
    QLayoutItem* deleteItem;
    while((deleteItem = gLay->takeAt(0)) != nullptr){
        if(deleteItem->widget() != nullptr){
            delete (deleteItem->widget());
        }
        delete deleteItem;
    }
}

void MainWindow::createListProducts(int index, const QString &prefix)
{
    sublist.clear();
    sublist.push_back(products[index]);
    for(size_t i = index + 1; i < products.size(); i++){
        QString id = products[i].getId();
        bool condition = id.startsWith(prefix);
        if(condition){
            sublist.push_back(products[i]);
        }
    }
}

void MainWindow::addWidgets(vector<Product> &list)
{
    size_t index = 0;
    int i = 0;
    int j = 0;
    bool stateAdd = true;
    while(stateAdd){
        if(j < 4){
            ProductWidget * product = new ProductWidget();
            product->setFixedSize(200, 300);
            product->addInformation(list[index++]);
            gLay->addWidget(product, i, j);
            j++;
        }
        else if(j >= 4){
            i++;
            j = 0;
        }
        if(index >= list.size())
            stateAdd = false;

    }
    ui->scrollContent->setLayout(gLay);
}

void MainWindow::sortByMinorPrice(int selectList)
{
    if(selectList == 0){
        sort(products.begin(), products.end(), [](Product &p, Product &p1){
            return p.getPriceProduct() < p1.getPriceProduct();
        });
        addWidget();
    }
    else if(selectList == 1){
        sort(sublist.begin(), sublist.end(), [](Product &p, Product &p1){
            return p.getPriceProduct() < p1.getPriceProduct();
        });
        addWidgets(sublist);
    }
    else if(selectList == 2){
        sort(temporalList.begin(), temporalList.end(), [](Product &p, Product &p1){
            return p.getPriceProduct() < p1.getPriceProduct();
        });
        addWidgets(temporalList);
    }
}

void MainWindow::sortByMajorPrice(int selectlist)
{
    if(selectlist == 0){
        sort(products.begin(), products.end(), [](Product &p, Product &p1){
            return p.getPriceProduct() > p1.getPriceProduct();
        });
        addWidget();
    }
    else if(selectlist == 1){
        sort(sublist.begin(), sublist.end(), [](Product &p, Product &p1){
            return p.getPriceProduct() > p1.getPriceProduct();
        });
        addWidgets(sublist);
    }
    else if(selectlist == 2){
        sort(temporalList.begin(), temporalList.end(), [](Product &p, Product &p1){
            return p.getPriceProduct() > p1.getPriceProduct();
        });
        addWidgets(temporalList);
    }
}

void MainWindow::searchCoincidences(const QString &wordSearch)
{
    temporalList.clear();
    int selectList = ui->comboBox->currentIndex();
    if(selectList == 0){
        auto it = products.begin();
        while(it != products.end()){
            QString currentWord = it->getNameProduct();
            bool comparator = currentWord.contains(wordSearch, Qt::CaseInsensitive);
            if(comparator){
                temporalList.push_back(*it);
            }
            it++;
        }
    }
    else{
        auto it = sublist.begin();
        while(it != sublist.end()){
            QString currentWord = it->getNameProduct();
            bool comparator = currentWord.contains(wordSearch, Qt::CaseInsensitive);
            if(comparator){
                temporalList.push_back(*it);
            }
            it++;
        }
    }
    if(temporalList.size() > 0){
        deleteWidgets();
        addWidgets(temporalList);
    }
    else {
        deleteWidgets();
    }
}

void MainWindow::on_usernameLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableLoginPB();
}

void MainWindow::on_paswordLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableLoginPB();
}

void MainWindow::on_newUserLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSignInPB();
}

void MainWindow::on_emailLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSignInPB();
}

void MainWindow::on_newPasswordLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableSignInPB();
}

void MainWindow::on_signInPB_clicked()
{
    QJsonObject jsonObjAux = dbJson;
    QJsonObject jsonObj;
    QMessageBox message;
    User user;
    user.setUserName(ui->newUserLE->text());
    user.setEmail(ui->emailLE->text());
    user.setPassword(ui->newPasswordLE->text());
    int factorOfTheNewUser = validateNewUser(user.getUserName(), user.getEmail());
    if(validateEmail(user.getEmail()) && factorOfTheNewUser == 2){
        users.push_back(user);
        jsonObj["name"] = user.getUserName();
        jsonObj["email"] = user.getEmail();
        jsonObj["password"] = user.getPassword();
        dbArray.append(jsonObj);
        dbJson["users"] = dbArray;
        message.setText("A new user created");
        message.setIcon(QMessageBox::Information);
        message.exec();
    }
    else if(factorOfTheNewUser < 2){
        message.setText("Error for the creation the new user\n"
        "Another user have this information");
        message.setIcon(QMessageBox::Warning);
        message.exec();
    }
    else{
        message.setText("Error an invalid format to email");
        message.setIcon(QMessageBox::Warning);
        message.exec();
    }
    ui->newUserLE->clear();
    ui->emailLE->clear();
    ui->newPasswordLE->clear();
}

void MainWindow::on_loginPB_clicked()
{
    validateUser();
    sortByUserID();
    sortByEmail();
    ui->usernameLE->clear();
    ui->paswordLE->clear();
}

void MainWindow::openFile()
{
    QString name;
    name = QFileDialog::getOpenFileName(this, "Select Database", "", "JSON file (*.json)");
    if(name.length() > 0){
        dbFile.setFileName(name);
        ui->LoginGB->setEnabled(true);
        ui->sigInGB->setEnabled(true);
        loadDB();
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    deleteWidgets();
    int firstIndex;
    int selectList = 0;
    ui->sortBy->setCurrentIndex(0);
    ui->searchText->setText("");
    switch(index){
    case 1:
        firstIndex = findFirstProduct("AB01");
        createListProducts(firstIndex, "AB");
        selectList = 1;
        break;
    case 2:
        firstIndex = findFirstProduct("L01");
        createListProducts(firstIndex, "L");
        selectList = 1;
        break;
    case 3:
        firstIndex = findFirstProduct("E01");
        createListProducts(firstIndex, "E");
        selectList = 1;
        break;
    case 4:
        firstIndex = findFirstProduct("HC01");
        createListProducts(firstIndex, "HC");
        selectList = 1;
        break;
    case 5:
        firstIndex = findFirstProduct("D01");
        createListProducts(firstIndex, "D");
        selectList = 1;
        break;
    }
    if(selectList == 0){
        addWidget();
        if(sublist.size() > 0)
            sublist.clear();
    }
    else
        addWidgets(sublist);
}

void MainWindow::on_sortBy_currentIndexChanged(int index)
{
    int selectList = -1;
    int currentDepartament = ui->comboBox->currentIndex();
    int sizeWordSearch = ui->searchText->text().length();
    if(currentDepartament == 0 && sizeWordSearch == 0)
        selectList = 0;
    else if(currentDepartament > 0 && sizeWordSearch == 0)
        selectList = 1;
    else {
        selectList = 2;
    }
    switch (index) {
        case 1:
            deleteWidgets();
            sortByMinorPrice(selectList);
            break;
        case 2:
            deleteWidgets();
            sortByMajorPrice(selectList);
            break;
    }
}


void MainWindow::on_searchText_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    QString wordSearch = ui->searchText->text();
    if(wordSearch.size() > 0){
        searchCoincidences(wordSearch);
    }
    else {
        deleteWidgets();
        temporalList.clear();
        int currentDepartament = ui->comboBox->currentIndex();
        int selectSort = ui->sortBy->currentIndex();
        int selectList = -1;
        if(currentDepartament == 0)
            selectList = 0;
        else
            selectList = 1;
        if(selectSort == 0){
            if(selectList == 0)
                addWidget();
            else
                addWidgets(sublist);
        }
        else if(selectSort == 1)
            sortByMinorPrice(selectList);
        else if(selectSort == 2)
            sortByMajorPrice(selectList);
    }
}
