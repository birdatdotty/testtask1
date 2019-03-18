#ifndef CELLBASE_H
#define CELLBASE_H

#include <QWidget>
#include <QGridLayout>

class ItemBase;

class CellBase : public QWidget
{
  Q_OBJECT
public:
  explicit CellBase(ItemBase* item, QPair<int,int> part, QWidget* parent = nullptr);

  void insertCell(ItemBase* item, QPair<int,int> part);
  void deleteCell();
  virtual void finished();

protected:
  void paintEvent(QPaintEvent*) override;
  void dragEnterEvent(QDragEnterEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;


  QGridLayout mainLayout;

  ItemBase* item;
  QPair<int,int> part;
  QPair<int,int> size;
  QPair<int,int> position;

};

#endif // CELLBASE_H
