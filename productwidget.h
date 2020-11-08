#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QMainWindow>
#include <QDebug>
#include "product.h"
namespace Ui {
class ProductWidget;
}

class ProductWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductWidget(QWidget *parent = nullptr);
    ~ProductWidget();
    void addInformation(const Product &product);

private slots:
    void on_numberProducts_valueChanged(const QString &arg1);
    void on_addPB_clicked();

signals:
    void addItem(QString id, int amount);
private:
    Ui::ProductWidget *ui;
    QString productId;
};

#endif // PRODUCTWIDGET_H
