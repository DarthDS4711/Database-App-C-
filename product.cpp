#include "product.h"

QString Product::getId() const
{
    return id;
}

void Product::setId(const QString &value)
{
    id = value;
}

QString Product::getNameProduct() const
{
    return nameProduct;
}

void Product::setNameProduct(const QString &value)
{
    nameProduct = value;
}

double Product::getPriceProduct() const
{
    return priceProduct;
}

void Product::setPriceProduct(double value)
{
    priceProduct = value;
}

Product::Product()
{

}
