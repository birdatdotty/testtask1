#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QHBoxLayout>

class Inventory;
class Inventory1;
class Shop;

class Game : public QWidget
{
  Q_OBJECT
public:
  explicit Game(QWidget *parent = nullptr);

signals:

public slots:

private:
  QHBoxLayout mainLayout;
  Inventory *inventory;
  Inventory1 *inventory1;
  Shop *shop;

};

#endif // GAME_H
