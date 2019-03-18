#ifndef INVENTORY1_H
#define INVENTORY1_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>

#include "config.h"

class CellInventar;
//class Item;
class ItemBase;


class Inventory1 : public QWidget
{
  Q_OBJECT
public:
  explicit Inventory1(QWidget *parent = nullptr);
  bool test(QPair<int,int> part, QPair<int,int> area);
  bool testType(QPair<int,int> position, QString type);
  QVector<CellInventar*> insert(ItemBase *item, QPair<int, int> position);
  void addElement (ItemBase*, int row, int column);

private:
  QHBoxLayout mainLayout;
  QTableWidget *tableWidget;

  CellInventar* map [INVETAR_ROW][INVETAR_COLUMN];



private slots:
  void createTable();
  void populateTable();
};

#endif // INVENTORY1_H
