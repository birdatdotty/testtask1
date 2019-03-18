//https://openhome.cc/Gossip/Qt4Gossip/QPixmapQBitmapQImageQPicture.html
// https://stackoverflow.com/questions/3206925/resizing-a-cells-height-and-witdth-and-loading-an-image-in-qtablewidget

#include "Inventory.h"
//#include "DropBox.h"
//#include "InventoryCellOld.h"
#include "InventoryCell.h"
#include "Item.h"
#include <QHeaderView>
#include <QPushButton>


#include "Apple.h"
#include "Banana.h"


Inventory::Inventory(QWidget *parent)
  : QWidget(parent),
    tableWidget(new QTableWidget)
{
  mainLayout.addWidget(tableWidget);
  createTable();
  populateTable();


  insert(new Banana(14),qMakePair(1,1));

  setLayout(&mainLayout);
}


bool Inventory::test(QPair<int, int> part, QPair<int,int> area)
{
  if (part.first + area.first > INVETAR_ROW)
    return false;
  if (part.second + area.second > INVETAR_COLUMN)
    return false;

  for (int r = part.first; r < part.first + area.first; r++)
    for (int c = part.second; c < part.second + area.second; c++)
      {
        InventoryCell* cell = map[r][c];
        if (!cell->isFree())
          return false;
      }

  return true;
}

void Inventory::insert(Item *item, QPair<int, int> position)
{
  int r = position.first,
      c = position.second;
//  InventoryCell* cell = map[r][c];
  QPair<int,int> size = item->getSize();
  for (int row = 0; row < size.first; row++)
    for (int column = 0; column < size.second; column++)
      {
        map[r+row][c+column]->insertCell(item,qMakePair(row,column));
      }

}

void Inventory::createTable()
{
  tableWidget->setRowCount(INVETAR_ROW);
  tableWidget->setColumnCount(INVETAR_COLUMN);

  tableWidget->horizontalHeader()->setDefaultSectionSize(LEN_SIDE);
  tableWidget->verticalHeader()->setDefaultSectionSize(LEN_SIDE);
  tableWidget->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
  tableWidget->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);

}

void Inventory::populateTable()
{
  for (int r = 0; r < INVETAR_ROW; ++r)
    for (int c = 0; c < INVETAR_COLUMN; ++c)
      {

        InventoryCell* cell = new InventoryCell(qMakePair(r,c), this);
        tableWidget->setCellWidget(r, c, cell);
        map[r][c] = cell;
      }
}

void Inventory::clearTable()
{
  items.clear();
}
