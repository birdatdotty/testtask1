#ifndef INVENTORYCELLOLD_H
#define INVENTORYCELLOLD_H

#include "BaseCell.h"

class InventoryCellOld: public BaseCell
{
  Q_OBJECT
public:
  InventoryCellOld(QPixmap *pixmap = nullptr, int count = 0);

signals:

protected:
  void paintEvent(QPaintEvent*) override;
  void drawCount(QPainter &painter, int count);

  void dragEnterEvent(QDragEnterEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;


private:
  QPixmap *pixmap;
  int count;

};

#endif // INVENTORYCELL_H
