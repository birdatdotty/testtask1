#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QPixmap>
#include <QGridLayout>

class InventoryCell;

class Item : public QWidget
{
  Q_OBJECT
  public:
    explicit Item(QString name, QString img, QPair<int,int> size, int count = 1);
    explicit Item(Item*);
    explicit Item();

    void update(QString name, QString img, QPair<int,int> size, int count = 1);

    QPair<int,int> getSize() const;
    QString getName() const;
    QString getImg() const;
    int getCount() const;
    QPair<int,int> getSize();

    void addCell(InventoryCell* cell);
    void countDown(int n = 1);
    void CountInc(int n = 1);

    void setCount(int newCount);
    void repaintCells();

    QPixmap *pixmap;


  signals:

  public slots:

  protected:
    QGridLayout mainLayout;
    QString name; // тип предмета
    QString img; // путь к изображению
    QPair<int,int> size; // количество ячеек по осям row, column

    int count;

  private:
    QVector<InventoryCell*> cells;
};

#endif // ITEM_H
