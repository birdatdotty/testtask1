#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "Db.h"

class ShopRow;
class ItemBase;

class Shop : public QWidget
{
  Q_OBJECT
public:
  explicit Shop(QWidget *parent = nullptr);
  void append(QList<ItemStruct>);

signals:

public slots:

private:
  QVBoxLayout mainLayout;
  QLabel label;
  QVector<ShopRow*> rows;

  QList<ItemBase*> items;

};

#endif // SHOP_H
