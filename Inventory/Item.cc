#include "Item.h"

#include "InventoryCell.h"

Item::Item(QString name, QString img, QPair<int,int> size, int count)
  : QWidget(nullptr),
    name(name),
    img(img),
    size(size),
    count(count)
{
  setLayout(&mainLayout);
  pixmap = new QPixmap(img);
}

Item::Item(Item *orig)
  : name(orig->name),
    img(orig->img),
    size(orig->size),
    count(orig->count)
{
  pixmap = new QPixmap(orig->img);
  setLayout(&mainLayout);
}

Item::Item()
  : name(""), img(""), size(qMakePair(1,1)), count(0)
{
setLayout(&mainLayout);
}

void Item::update(QString name, QString img, QPair<int, int> size, int count)
{
  this->name = name;
  this->img = img;
  this->size = size;
  this->count = count;
}

QPair<int, int> Item::getSize() const
{
  return size;
}

QString Item::getName() const
{
  return name;
}

QString Item::getImg() const
{
  return img;
}

int Item::getCount() const
{
  return count;
}

QPair<int, int> Item::getSize()
{
  return size;
}

void Item::addCell(InventoryCell *cell)
{
  cells.append(cell);
}

void Item::countDown(int n)
{
  count -= n;
}

void Item::CountInc(int n)
{
  count += n;
}

void Item::setCount(int newCount)
{
  count = newCount;
}

void Item::repaintCells()
{
  for (InventoryCell *cell: cells)
    {
      cell->repaintCell();
    }
}
