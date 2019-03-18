#include "Shop.h"
#include "ShopRow.h"

#include "Apple1.h"
#include "Banana1.h"
#include "Ananas1.h"

Shop::Shop(QWidget *parent)
  : QWidget(parent),
    label("Магазин:")
{
  mainLayout.setAlignment(Qt::AlignTop);
  mainLayout.addWidget(&label);

  setLayout(&mainLayout);
}

#include <QDebug>
void Shop::append(QList<ItemStruct> list)
{
  qInfo() << list.size();
  for (int i = 0; i < list.size(); i++) {
    int row = list[i].row,
        column = list[i].column;
  //  items.append(new ItemBase("ananas", ":/fruit/ananas", qMakePair(2,2), -1));
    ItemBase* item = new ItemBase(list[i].item, list[i].img, qMakePair(row,column), -1);
    qInfo() << list[i].item << list[i].img << list[i].row << list[i].column;
    items.append(item);
    ShopRow *shopRow = new ShopRow(item);
    rows.append(shopRow);
    mainLayout.addWidget(shopRow);
  }
}
