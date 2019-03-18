#include "Inventory1.h"
#include "CellInventar.h"
#include "BaseItem.h"

#include <QHeaderView>
#include <QPushButton>


#include "CellInventar.h"
#include "ItemBase.h"

#include "Apple.h"
#include "Apple1.h"
#include "Banana1.h"


Inventory1::Inventory1(QWidget *parent)
  : QWidget(parent),
    tableWidget(new QTableWidget)
{
  mainLayout.addWidget(tableWidget);
  createTable();
  populateTable();


//  insert(new Banana(14),qMakePair(1,1));
//  CellInventar* cell = new CellInventar(new Apple1(2), qMakePair(r,c), this);
//  insert(new Banana1(44),qMakePair(2,1));

  setLayout(&mainLayout);
}

bool Inventory1::test(QPair<int, int> part, QPair<int,int> area)
{
  if (part.first + area.first > INVETAR_ROW)
    return false;
  if (part.second + area.second > INVETAR_COLUMN)
    return false;

  for (int r = part.first; r < part.first + area.first; r++)
    for (int c = part.second; c < part.second + area.second; c++)
      {
        CellInventar* cell = map[r][c];
        if (!cell->isFree())
          return false;
      }

  return true;
}

bool Inventory1::testType(QPair<int, int> position, QString type)
{
  return (map[position.first][position.second]->testType(type));
}

QVector<CellInventar*> Inventory1::insert(ItemBase *item, QPair<int, int> position)
{
  int r = position.first,
      c = position.second;

  QVector<CellInventar*> cells;

  QPair<int,int> size = item->getSize();
  for (int row = 0; row < size.first; row++)
    for (int column = 0; column < size.second; column++)
      {
        CellInventar *cell = map[r+row][c+column];
        cell->insertCell(item,qMakePair(row,column));
        cells.append(cell);
//        map[r+row][c+column]->insertCell(item,qMakePair(row,column));
      }

  return cells;

}

void Inventory1::addElement(ItemBase *newItem, int row, int column)
{
  QVector<CellInventar*> cells = insert(newItem,qMakePair(row, column));
  for (auto cell: cells)
    newItem->addCell(cell);

}

void Inventory1::createTable()
{
  tableWidget->setRowCount(INVETAR_ROW);
  tableWidget->setColumnCount(INVETAR_COLUMN);

  tableWidget->horizontalHeader()->setDefaultSectionSize(LEN_SIDE);
  tableWidget->verticalHeader()->setDefaultSectionSize(LEN_SIDE);
  tableWidget->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
  tableWidget->verticalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);

}

void Inventory1::populateTable()
{
  Inventory1 *inventory1 = const_cast<Inventory1*>(this);
  for (int r = 0; r < INVETAR_ROW; ++r)
    for (int c = 0; c < INVETAR_COLUMN; ++c)
      {
        CellInventar* cell =
            new CellInventar(new ItemBase(), qMakePair(r,c), inventory1);
//        CellInventar* cell = new CellInventar(new Apple1(2), qMakePair(r,c), this);

        tableWidget->setCellWidget(r, c, cell);
        map[r][c] = cell;
      }
}
