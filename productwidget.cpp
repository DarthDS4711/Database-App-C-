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
    if(nameProduct.length() > 33)
        nameProduct.insert(33, "\n");
    if(nameProduct.length() > 66)
        nameProduct.insert(66, "\n");
    price.setNum(product.getPriceProduct());
    ui->PriceLabel->setText(price);
    ui->IdLabel->setText(product.getId());
    ui->nameLabel->setText(nameProduct);
    ui->ImageLabel->setFixedSize(150, 150);
    QString imageId = product.getId();
    productId = imageId;
    QPixmap pix(":/Img/imgs/" + imageId + ".jpg");
    ui->ImageLabel->setPixmap(pix.scaled(150, 150, Qt::KeepAspectRatio, Qt::FastTransformation));
}

void ProductWidget::on_numberProducts_valueChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    int numberProductus = ui->numberProducts->value();
    if(numberProductus > 0){
        ui->addPB->setEnabled(true);
    }
    else{
        ui->addPB->setEnabled(false);
    }
}

void ProductWidget::on_addPB_clicked()
{
    emit addItem(productId, ui->numberProducts->value());
    ui->numberProducts->setValue(0);
}
