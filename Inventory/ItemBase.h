#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QWidget>
#include <QGridLayout>
#include <QDataStream>

class CellBase;

class ItemBase: public QObject
{
  Q_OBJECT
public:
  explicit ItemBase(QString type, QString img, QPair<int,int> size, int count = 1);
  explicit ItemBase(ItemBase*);
  explicit ItemBase();
  ~ItemBase();

  void update(QString type, QString img, QPair<int,int> size, int count = 1);
  bool isFree();
  void clear();

  QPair<int,int> getSize() const;
  QString getType() const;
  QString getImg() const;
  int getCount() const;
  QPixmap getPixMap() const;

  void addCell(CellBase* cell);
  void countDec(int n = 1);
  void countInc(int n = 1);

  void repaintCells();
  QByteArray getItemData();

private:
  QGridLayout mainLayout;
  QPixmap pixmap; // изображение
  QString type; // тип предмета
  QString img; // путь к изображению
  QPair<int,int> size; // количество ячеек по осям row, column
  int count; // кол-во предметов
  QVector<CellBase*> cells; // ячейки занятые предметом
};

#endif // ITEMBASE_H
