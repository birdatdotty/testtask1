#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>

#include "DropBox.h"
#include "config.h"

class InventoryCell;
class Item;

class Inventory : public QWidget
{
  Q_OBJECT
public:
  explicit Inventory(QWidget *parent = nullptr);
  bool test(QPair<int,int> part, QPair<int,int> area);
  void insert(Item *item, QPair<int, int> position);

signals:

public slots:

private:
  QHBoxLayout mainLayout;
  QTableWidget *tableWidget;

//  Item *apple;
  QVector<DropBox*> items;

  InventoryCell* map [INVETAR_ROW][INVETAR_COLUMN];



private slots:
  void createTable();
  void populateTable();
  void clearTable();
};

#endif // INVENTORY_H
