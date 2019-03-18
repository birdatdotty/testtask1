#ifndef SHOPROW_H
#define SHOPROW_H

#include <QWidget>
#include <QGridLayout>

class ItemBase;
class InventoryCell;

class ShopRow : public QWidget
{
  Q_OBJECT
public:
  explicit ShopRow(ItemBase* item, QWidget *parent = nullptr);

signals:

public slots:

private:
  QGridLayout mainLayout;


};

#endif // SHOPROW_H
