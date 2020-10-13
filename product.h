#ifndef PRODUCT_H
#define PRODUCT_H
#include <QString>
class Product
{
private:
    QString id;
    QString nameProduct;
    double priceProduct;
public:
    Product();
    QString getId() const;
    void setId(const QString &value);
    QString getNameProduct() const;
    void setNameProduct(const QString &value);
    double getPriceProduct() const;
    void setPriceProduct(double value);
};

#endif // PRODUCT_H
