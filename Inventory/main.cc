#include "MainWindow.h"
#include <QApplication>

#include "Db.h"

Db* db;

int main(int argc, char *argv[])
{

  db = new Db;
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
