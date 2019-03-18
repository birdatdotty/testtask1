#include "config.h"

#include "Inventory.h"
#include "InventoryCell.h"
#include "Item.h"

#include <QLabel>
#include <QPainter>
#include <QRect>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>


InventoryCell::InventoryCell(QPair<int,int> position, Item* item, QPair<int,int> part,
                             Inventory* parent)
  : QWidget(),
    item(item),
    part(part),
    size(item->getSize()),
    position(position)
{
  inventory = parent;
  setMinimumSize(LEN_SIDE, LEN_SIDE);
  setLayout(&mainLayout);
  setAcceptDrops(true);
}

InventoryCell::InventoryCell(QPair<int,int> position, Inventory* parent)
  : QWidget(),
    item(new Item()),
    part(qMakePair(0,0)),
    size(qMakePair(1,1)),
    position(position)
{
  inventory = parent;
  setLayout(&mainLayout);
  setAcceptDrops(true);
}

bool InventoryCell::isFree() const
{
  return (item->getCount() == 0);
}

void InventoryCell::insertCell(Item *item, QPair<int, int> part)
{
  this->item = item;
  this->part = part;
  item->addCell(this);
  repaint(rect());
}

void InventoryCell::repaintCell()
{
  repaint(rect());
}

void InventoryCell::rightClick(QMouseEvent *event)
{
  if (item->getCount() > 0)
    {
      item->countDown();
      item->repaintCells();
    }
  else {
      Item *tmpItem = item;
      item = new Item();
      delete tmpItem;
      item->repaintCells();
    }
}

void InventoryCell::leftClick(QMouseEvent *event)
{
  if (item->getCount() > 0)
    {
      Item *child = new Item(item);
      if (item->getCount() < 0)
        child->setCount(1);

      QPixmap pixmap = *item->pixmap;

      QByteArray itemData;
      QDataStream dataStream(&itemData, QIODevice::WriteOnly);
      dataStream << child->getName() << child->getImg() << size.first << size.second << child->getCount();

      QMimeData *mimeData = new QMimeData;
      mimeData->setData("item/data", itemData);

      QDrag *drag = new QDrag(this);
      drag->setMimeData(mimeData);
      drag->setPixmap(pixmap);

      QPixmap tempPixmap = pixmap;
      QPainter painter(this);
      painter.begin(&tempPixmap);
      painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
      painter.end();

      if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        delete child;
    }

}

void InventoryCell::paintEvent(QPaintEvent *)
{
  if (item)
    if(item->getCount()>0)
      {
        QPainter painter(this);
        QPixmap *pixmap = item->pixmap;

        int column = part.first;
        int row = part.second;

        painter.save();
        painter.translate(-LEN_SIDE*row, 0);
        painter.translate(0, -LEN_SIDE*column);
        painter.drawPixmap(pixmap->rect(), *pixmap);
        painter.restore();

        int count = item->getCount();//item->count;
        if (part.first == size.first - 1)
          if (part.second == size.second - 1)
            if (count > 0)
              painter.drawText(QPoint(LEN_SIDE - 40, LEN_SIDE - 10), QString::number(count));

        painter.save();
        painter.setPen(QPen(Qt::blue, 6, Qt::SolidLine, Qt::FlatCap));

        if (part.first == 0)
          {
            painter.drawLine(0, 0, LEN_SIDE, 0);
          }
        if (part.second == 0)
          {
            painter.drawLine(0, 0, 0, LEN_SIDE);
          }
        if (part.first == size.first - 1)
          {
            painter.drawLine(0, LEN_SIDE, LEN_SIDE, LEN_SIDE);
          }
        if (part.second == size.second - 1)
          {
            painter.drawLine(LEN_SIDE, 0, LEN_SIDE, LEN_SIDE);
          }
        painter.restore();
      }
}

// Проверяем данные что перетащили
void InventoryCell::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("item/data"))
    if (event->source() != this) {
      event->setDropAction(Qt::MoveAction);

      //test size
      QByteArray pieceData = event->mimeData()->data("item/data");
      QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
      QString name, img;
      int row, column, count;
      dataStream >> name >> img >> row >> column >> count;

      if (inventory->test(position, qMakePair(row, column)))
        event->accept();
      else
        event->ignore();
    }
}

// Начинаем перетаскивание (Drag)
void InventoryCell::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::RightButton)
    rightClick(event);

  if (event->button() == Qt::LeftButton)
    leftClick(event);
}

// Получаем данные, что перетащили
void InventoryCell::dropEvent(QDropEvent *event)
{
  if (event->mimeData()->hasFormat("item/data"))
    {
      QByteArray pieceData = event->mimeData()->data("item/data");
      QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
      QString name, img;
      int sizeX, sizeY, count;
      dataStream >> name >> img >> sizeX >> sizeY >> count;
      if (item->getCount()>0)
        {
          if (item->getName() == name)
            item->CountInc(count);
          else
            item = new Item(name,img,qMakePair(sizeY,sizeX),count);
        }
      else
        {
          item = new Item(name,img,qMakePair(sizeX,sizeY),count);
          inventory->insert(item,position);

        }
//      repaint(rect());
//      repaintCell();
      item->repaintCells();
      event->accept();
    }
}

