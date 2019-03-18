#include "Db.h"
#include "config.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>

#include <QDebug>

Db::Db(QObject *parent) : QObject(parent)
{
  open(DB_FILE);
}

bool Db::createTables()
{
//  db->
  QSqlQuery query;
  bool status = query.exec("CREATE TABLE IF NOT EXISTS `ITEMS` ("
                           "`TYPE`  TEXT NOT NULL,"
                           "`IMG`   TEXT NOT NULL,"
                           "`ROW` INTEGER NOT NULL,"
                           "`COLUMN` INTEGER NOT NULL"
                           ");");

  if (!status)
    return status;

  status = query.exec("CREATE TABLE IF NOT EXISTS `INVENTAR` ("
                      "`TYPE`  TEXT NOT NULL,"
                      "`CELLX` INTEGER NOT NULL,"
                      "`CELLY` INTEGER NOT NULL"
                      ");");

  return status;
}

void Db::populate()
{
  qInfo() << "void Db::populate()";
  QString addItem = "INSERT OR REPLACE INTO ITEMS (TYPE, IMG, ROW, COLUMN)"
      "VALUES ('%1','%2','%3','%4')";

  QSqlQuery query;
  query.exec(addItem.arg("apple", ":/fruit/apple", "1", "1"));
  query.exec(addItem.arg("banana", ":/fruit/banana", "1", "2"));
  query.exec(addItem.arg("ananas", ":/fruit/ananas", "2", "2"));
//      insert or replace into Book (ID, Name, TypeID, Level, Seen) values (
//     (select ID from Book where Name = "SearchName"),
//     "SearchName",
//      5,
//      6,
//      (select Seen from Book where Name = "SearchName"));
}

QList<ItemStruct> Db::getElements()
{
  QList<ItemStruct> list;
  qInfo() << 123;
  QSqlQuery query ("select * from ITEMS;");

  while (query.next()) {
//      QString name = query.value(0).toString();
//      int salary = query.value(1).toInt();
//      qDebug() << name << salary;
      ItemStruct item;
      item.item = query.value(0).toString();
      item.img = query.value(1).toString();
      item.row = query.value(2).toInt();
      item.column = query.value(3).toInt();


      list.append(item);
  }

//  qInfo() << list[1].row;

  ItemStruct item1;
  return list;
}

bool Db::open(QString file)
{
  QSqlDatabase tmpDb;
  tmpDb = QSqlDatabase::addDatabase("QSQLITE");

  bool fileExist = QFile::exists(file);
  if(fileExist)
    qInfo() << file << "exist!";
  else qInfo("file don't found");

  tmpDb.setDatabaseName(file);
  if (!tmpDb.open())
    return false;

  db = &tmpDb;

  createTables();

  if(!fileExist)
    populate();

  return true;
}
