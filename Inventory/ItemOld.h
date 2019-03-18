#ifndef ITEMOLD_H
#define ITEMOLD_H

#include <QLabel>

class ItemOld : public QLabel
{
  Q_OBJECT
public:
  explicit ItemOld(QPixmap pixImg);

protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

signals:

public slots:
};

#endif // ITEM_H
