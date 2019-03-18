// https://doc.qt.io/qt-5/qtwidgets-widgets-icons-example.html
#include "ItemOld.h"

#include <QPainter>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>


ItemOld::ItemOld(QPixmap pixImg)
{
  setAlignment(Qt::AlignCenter);
  setFrameShape(QFrame::Box);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
  setMinimumSize(200, 200);
  setMaximumSize(200, 200);
  setPixmap(pixImg);
}

void ItemOld::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
      QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
      QDataStream dataStream(&itemData, QIODevice::ReadOnly);

      QPixmap pixmap;
      QPoint offset;
      dataStream >> pixmap >> offset;

      QLabel *newIcon = new QLabel(this);
      newIcon->setPixmap(pixmap);
      newIcon->move(event->pos() - offset);
      newIcon->show();
      newIcon->setAttribute(Qt::WA_DeleteOnClose);

      if (event->source() == this) {
          event->setDropAction(Qt::MoveAction);
          event->accept();
      } else {
          event->acceptProposedAction();
      }
  } else {
      event->ignore();
  }
}

void ItemOld::mousePressEvent(QMouseEvent *event)
{
  QLabel *child = static_cast<QLabel*>(this);
  qInfo() << __FILE__ << ":" << __LINE__  << "child:" << child;
  if (!child)
      return;

  QPixmap pixmap = *child->pixmap();

  QByteArray itemData;
  QDataStream dataStream(&itemData, QIODevice::WriteOnly);
  dataStream << pixmap << QPoint(event->pos() - child->pos());
  qInfo() << __FILE__ << ":" << __LINE__  << pixmap;

  QMimeData *mimeData = new QMimeData;
  mimeData->setData("application/x-dnditemdata", itemData);

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);

  QPixmap tempPixmap = pixmap;
  QPainter painter;
  painter.begin(&tempPixmap);
  painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
  painter.end();

  child->setPixmap(tempPixmap);

  if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
      child->close();
  else {
      child->show();
      child->setPixmap(pixmap);
  }
}

