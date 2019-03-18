#include "CellInventar.h"

#include "ItemBase.h"
#include "Inventory1.h"

#include <QRect>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>
#include <QPair>


CellInventar::CellInventar(ItemBase* item, QPair<int,int> part, Inventory1* inventory1, QWidget* parent)
  : CellBase (item,part,parent),
    inventory1(inventory1)
{
  setAcceptDrops(true);
}

bool CellInventar::isFree()
{
  return (item->isFree());
}

bool CellInventar::testType(QString type)
{
  return (type == item->getType());
}

void CellInventar::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("item/data"))
    {
      QByteArray pieceData = event->mimeData()->data("item/data");
      QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
      QString type, img;
      int columns, sizeY, count;
      dataStream >> type >> img >> columns >> sizeY >> count;

      if (
            (inventory1->testType(qMakePair(columns, sizeY), type)) |
            (inventory1->test(qMakePair(columns, sizeY), position))
          )
        event->accept();
      else
        event->ignore();
    }

}

#include <QDebug>
void CellInventar::dropEvent(QDropEvent *event)
{
  if (event->mimeData()->hasFormat("item/data"))
    {
      QByteArray pieceData = event->mimeData()->data("item/data");
      QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
      QString type, img;
      int columns, sizeY, count;
      dataStream >> type >> img >> columns >> sizeY >> count;
      if (item->getType() == type)
        {
//          item->countInc(count);
          item->repaintCells();

          event->accept();
        }
      else
      if (inventory1->test(qMakePair(columns, sizeY), position))
        {
          ItemBase *newItem = new ItemBase(type, img, qMakePair(columns,sizeY), count);
          item->clear();
          QVector<CellInventar*> cells;
          cells = inventory1->insert(newItem,part);
          for (auto cell: cells)
            newItem->addCell(cell);

          event->accept();
        }
      else
        event->ignore();

      item->repaintCells();
    }

}

