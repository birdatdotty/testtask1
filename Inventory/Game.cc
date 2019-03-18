#include "Game.h"

#include "Inventory.h"
#include "Inventory1.h"
#include "Shop.h"

#include "Apple1.h"

#include "Db.h"
#include <QDebug>
extern Db* db;

Game::Game(QWidget *parent) : QWidget(parent)
{
  inventory1 = new Inventory1();
//  auto apple = new Apple1(16);
//  inventory1->addElement(apple, 1,2);

  shop = new Shop();
  QList<ItemStruct> items = db->getElements();
  shop->append(items);

  mainLayout.addWidget(inventory1);
  mainLayout.addWidget(shop);


  setLayout(&mainLayout);
}
