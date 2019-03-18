#ifndef INVENTORYCELL_H1
#define INVENTORYCELL_H1

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class Item;
class Inventory;

class InventoryCell: public QWidget
{
  public:
    InventoryCell(QPair<int,int> position, Item* item, QPair<int,int> part, Inventory* parent = nullptr);
    InventoryCell(QPair<int,int> position, Inventory* parent = nullptr);

    bool isFree() const;
    void insertCell(Item* item, QPair<int,int> part);
    void repaintCell();

  private:
    QGridLayout mainLayout;
    Item* item;
    QPair<int,int> part;
    QPair<int,int> size;
    Inventory* inventory;
    QPair<int,int> position;

    void rightClick(QMouseEvent *event);
    void leftClick(QMouseEvent *event);

  protected:
    void paintEvent(QPaintEvent*) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void dropEvent(QDropEvent *event) override;

};

#endif // INVENTORYCELL_H
