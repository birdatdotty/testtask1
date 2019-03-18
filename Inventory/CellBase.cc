#include "CellBase.h"
#include "ItemBase.h"

#include "config.h"

#include <QPainter>
#include <QRect>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>

#include <QDebug>


CellBase::CellBase(ItemBase* item, QPair<int,int> part, QWidget* parent)
  : QWidget(parent),
    item(item),
    part(part),
    position(part)
{
}

void CellBase::insertCell(ItemBase *item, QPair<int, int> part)
{
  if (this->item->getType() == item->getType())
    this->item->countInc(item->getCount());
  else
    this->item = item;

  this->part = part;

  repaint(rect());

}

void CellBase::deleteCell()
{
  size = qMakePair(1,1);
  part = qMakePair(1,1);
  item = new ItemBase();
  repaint(rect());
}

#include <QDebug>
void CellBase::finished()
{
  qInfo() << "void CellBase::finished()";
}

void CellBase::paintEvent(QPaintEvent *)
{
  if (item->getCount() != 0)
    {
      QPainter painter(this);
      QPixmap pixmap = item->getPixMap();

      int column = part.first;
      int row = part.second;

      painter.save();
      painter.translate(-LEN_SIDE*row, 0);
      painter.translate(0, -LEN_SIDE*column);
      painter.drawPixmap(pixmap.rect(), pixmap);
      painter.restore();

      int count = item->getCount();//item->count;
      if (part.first == item->getSize().first - 1)
        if (part.second == item->getSize().second - 1)
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
      if (part.first == item->getSize().first - 1)
        {
          painter.drawLine(0, LEN_SIDE, LEN_SIDE, LEN_SIDE);
        }
      if (part.second == item->getSize().second - 1)
        {
          painter.drawLine(LEN_SIDE, 0, LEN_SIDE, LEN_SIDE);
        }
      painter.restore();
    }

}

void CellBase::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("item/data"))
    {
//      if (event->source() != this) {
          event->setDropAction(Qt::MoveAction);
          event->accept();
          //      event->ignore();
//        }
    }
}

void CellBase::mousePressEvent(QMouseEvent *event)
{
  qInfo() << "void CellBase::mousePressEvent(QMouseEvent *event)";
  if (item->getCount() != 0)
    if(item->getType().size()>0)
    {
        int count = item->getCount();
      ItemBase *child = new ItemBase(item);
//      if (item->getCount() < 0)
//        child->setCount(1);

      QPixmap pixmap = item->getPixMap();

//      QByteArray itemData = item->getItemData();
//      QPair<int,int> size = item->getSize();
//      QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//      dataStream << child->getName() << child->getImg() << size.first << size.second << child->getCount();

      QMimeData *mimeData = new QMimeData;
      mimeData->setData("item/data", item->getItemData());

      QDrag *drag = new QDrag(this);
      drag->setMimeData(mimeData);
      drag->setPixmap(pixmap);

      QPixmap tempPixmap = pixmap;
      QPainter painter;
      painter.begin(&tempPixmap);
      painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
      painter.end();

      Qt::DropAction action = drag->exec();
      qInfo() << "drag->exec : " << action;
//      if (action == Qt::MoveAction)
//        item->countDec(count);

      if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        {
          qInfo() << __LINE__ << "if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)";
//          finished();
          delete child;
        }
    }

}
