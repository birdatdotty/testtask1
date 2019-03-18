#include "DropBox.h"
#include "config.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QLabel>
#include "InventoryCellOld.h"

DropBox::DropBox(QWidget *parent) : QLabel(parent)
{
  setMinimumSize(LEN_SIDE, LEN_SIDE);
  setMaximumSize(LEN_SIDE, LEN_SIDE);
  setAcceptDrops(true);
  setAutoFillBackground(true);

//  QPixmap pixImg(":/fruit/apple");
//  setPixmap(pixImg);
}
#include <QDebug>
void DropBox::dragEnterEvent(QDragEnterEvent *event)
{
//  setBackgroundRole(QPalette::Highlight);

//  event->acceptProposedAction();
////  emit changed(event->mimeData());
  const QMimeData *mime = event->mimeData();
  qInfo() << __FILE__ << ":" << __LINE__  << "void Item::dragEnterEvent(QDragEnterEvent *event)";
  if (
       mime->hasFormat("data/item") ||
       mime->hasFormat("data/item2")
     ) {
      qInfo() << QString(__FILE__) + ":" << __LINE__  << "if (event->mimeData()->hasFormat(\"application/x-dnditemdata\"))";
      QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
      QDataStream dataStream(&itemData, QIODevice::ReadOnly);

      QPixmap pixmap;
      QPoint offset;
      dataStream >> pixmap >> offset;
      qInfo() << __FILE__ << ":" << __LINE__  << "pixmap:"<<pixmap;
      qInfo() << __FILE__ << ":" << __LINE__  << "offset:" << offset ;

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

//void DropBox::dragMoveEvent(QDragMoveEvent *event)
//{

//}

//void DropBox::dragLeaveEvent(QDragLeaveEvent *event)
//{

//}
#include <QDebug>
void DropBox::dropEvent(QDropEvent *event)
{
  qInfo() << __FILE__ << ":" << __LINE__  << event->mimeData();
  qInfo() << __FILE__ << ":" << __LINE__  << event->source();
  qInfo() << __FILE__ << ":" << __LINE__  << event->source();
  if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
      QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
      QDataStream dataStream(&itemData, QIODevice::ReadOnly);
qInfo("event->mimeData()->hasFormat(\"application/x-dnditemdata\")");
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
          qInfo() << __FILE__ << ":" << __LINE__  << ">>>>" << event->source();
//          qInfo() << __FILE__ << ":" << __LINE__  << qobject_cast<QLabel*>(event->source())->pixmap();
          qInfo() << __FILE__ << ":" << __LINE__  << qobject_cast<InventoryCellOld*>(event->source());
          const QPixmap *pixMap = qobject_cast<QLabel*>(event->source())->pixmap();
          setPixmap(pixmap);

//          QPixmap pixImg(":/fruit/apple");
//          setPixmap(pixImg);
          qInfo() << __FILE__ << ":" << __LINE__  << "-------------";
      }
  } else if (event->mimeData()->hasFormat("data/item")) {
      QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
      QDataStream dataStream(&itemData, QIODevice::ReadOnly);
qInfo("event->mimeData()->hasFormat(\"data/item\")");
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
          qInfo() << __FILE__ << ":" << __LINE__  << ">>>>" << event->source();
//          qInfo() << __FILE__ << ":" << __LINE__  << qobject_cast<QLabel*>(event->source())->pixmap();
          qInfo() << __FILE__ << ":" << __LINE__  << qobject_cast<InventoryCellOld*>(event->source());
          const QPixmap *pixMap = qobject_cast<QLabel*>(event->source())->pixmap();
          setPixmap(pixmap);

//          QPixmap pixImg(":/fruit/apple");
//          setPixmap(pixImg);
          qInfo() << __FILE__ << ":" << __LINE__  << "-------------";
      }
  } else {
      event->ignore();
  }
}
