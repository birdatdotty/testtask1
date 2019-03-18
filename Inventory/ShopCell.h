#ifndef SHOPCELL_H
#define SHOPCELL_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>


class ItemBase;

class ShopCell: public QWidget
{
  public:
    ShopCell(ItemBase* item, QPair<int,int> part, QWidget* parent = nullptr);

  private:
    QGridLayout mainLayout;


  protected:
    void paintEvent(QPaintEvent*) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
//    void dropEvent(QDropEvent *event) override;

    ItemBase* item;
    QPair<int,int> part;
    QPair<int,int> size;

};

#endif // INVENTORYCELL_H
