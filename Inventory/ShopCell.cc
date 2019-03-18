#include "config.h"

#include "ShopCell.h"
#include "ItemBase.h"

#include <QLabel>
#include <QPainter>
#include <QRect>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>

#include <QDebug>

ShopCell::ShopCell(ItemBase* item, QPair<int,int> part,
                             QWidget* parent)
  : QWidget(parent),
    item(item),
    part(part),
    size(item->getSize())
{
  setMinimumSize(LEN_SIDE, LEN_SIDE);
  setLayout(&mainLayout);
  setAcceptDrops(false);
}

void ShopCell::paintEvent(QPaintEvent *)
{
  if (item)
    if(item->getType().size()>0)
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
void ShopCell::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("item/data"))
    if (event->source() != this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    }
}

// Начинаем перетаскивание (Drag)
void ShopCell::mousePressEvent(QMouseEvent *event)
{
  if (item)
    if(item->getType().size()>0)
    {
      ItemBase *child = new ItemBase(item);
//      if (item->getCount() < 0)
//        child->setCount(1);

      QPixmap pixmap = item->getPixMap();

      QByteArray itemData;
      QDataStream dataStream(&itemData, QIODevice::WriteOnly);
      dataStream << child->getType() << child->getImg() << size.first << size.second << child->getCount();

      QMimeData *mimeData = new QMimeData;
      mimeData->setData("item/data", itemData);

      QDrag *drag = new QDrag(this);
      drag->setMimeData(mimeData);
      drag->setPixmap(pixmap);

      QPixmap tempPixmap = pixmap;
      QPainter painter;
      painter.begin(&tempPixmap);
      painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
      painter.end();

      if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        {
          qInfo() << __LINE__ << "drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)";

          delete child;
        }
    }
}

// Получаем данные, что перетащили
//void ShopCell::dropEvent(QDropEvent *event)
//{
//  if (event->mimeData()->hasFormat("item/data"))
//    {
//      QByteArray pieceData = event->mimeData()->data("item/data");
//      QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
//      QString name, img;
//      int row, sizeY, count;
//      dataStream >> name >> img >> row >> sizeY >> count;
//      event->accept();
//    }
//}

