#include "ShopRow.h"

#include "ItemBase.h"
#include "InventoryCell.h"
#include "ShopCell.h"

#include <QtDebug>

ShopRow::ShopRow(ItemBase* item, QWidget *parent) : QWidget(parent)
{
  QPair<int,int> size = item->getSize();
  int row = size.first,
      column = size.second;


  for (int r = 0; r < row; r++)
    for (int c = 0; c < column; c++)
      {
        QWidget *cell = new ShopCell(item, qMakePair(r,c));
        mainLayout.addWidget(cell, r, c);
      }

  setLayout(&mainLayout);
}
