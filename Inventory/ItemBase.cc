#include "ItemBase.h"
#include "CellBase.h"

ItemBase::ItemBase(QString type, QString img, QPair<int,int> size, int count)
  : pixmap(QPixmap(img)),
    type(type),
    img(img),
    size(size),
    count(count)
{}

ItemBase::ItemBase(ItemBase* item)
  : pixmap(item->pixmap),
    type(item->type),
    img(item->img),
    size(item->size)
{
  count = (item->count <= 0) ? 1 : item->count;
}

ItemBase::ItemBase()
  : count(0)
{}

ItemBase::~ItemBase()
{

}

void ItemBase::update(QString type, QString img, QPair<int, int> size, int count)
{
  pixmap = QPixmap(img);
  this->type = type;
  this->img = img;
  this->size = size;
  this->count = count;
}

bool ItemBase::isFree()
{
  return (count == 0);
}

void ItemBase::clear()
{
  for (CellBase* cell: cells)
    cell->deleteCell();
}

QPair<int,int> ItemBase::getSize() const
{
  return size;
}

QString ItemBase::getType() const
{
  return type;
}

QString ItemBase::getImg() const
{
  return img;
}

int ItemBase::getCount() const
{
  return count;
}

QPixmap ItemBase::getPixMap() const
{
  return pixmap;
}

void ItemBase::addCell(CellBase* cell)
{
  cells.append(cell);
}

void ItemBase::countDec(int n)
{
  count -= n;
  if (count == 0)
    {
      cells.clear();
      img = "";
      size = qMakePair(1,1);

    }
  repaintCells();
}

void ItemBase::countInc(int n)
{
  count += n;
}

#include <QDebug>
void ItemBase::repaintCells()
{
  // ????
  qInfo() << __LINE__ << cells;
  for (auto cell: cells)
    {
      qInfo() << __LINE__ << cell;
      cell->repaint();
    }
}

QByteArray ItemBase::getItemData()
{
  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << type << img << size.first << size.second << count;

  return itemData;
}

//ItemBase::
