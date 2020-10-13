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

private:
    Ui::ProductWidget *ui;
};

#endif // PRODUCTWIDGET_H
