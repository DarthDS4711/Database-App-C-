#include "productwidget.h"
#include "ui_productwidget.h"

ProductWidget::ProductWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductWidget)
{
    ui->setupUi(this);
}

ProductWidget::~ProductWidget()
{
    delete ui;
}

void ProductWidget::addInformation(const Product &product)
{
    QString price;
    QString nameProduct = product.getNameProduct();
    if(nameProduct.length() > 75){
        nameProduct.insert(25, "\n");
        nameProduct.insert(50, "\n");
        nameProduct.insert(75, "\n");
    }
    else {
        nameProduct.insert(25, "\n");
        nameProduct.insert(50, "\n");
    }
    price.setNum(product.getPriceProduct());
    ui->PriceLabel->setText(price);
    ui->IdLabel->setText(product.getId());
    ui->nameLabel->setFixedWidth(200);
    ui->nameLabel->setText(nameProduct);
    ui->ImageLabel->setFixedSize(200, 200);
    QString imageId = product.getId();
    QPixmap pix(":/Img/imgs/" + imageId + ".jpg");
    ui->ImageLabel->setPixmap(pix.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation));
}
