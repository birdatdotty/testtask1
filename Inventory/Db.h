#ifndef DB_H
#define DB_H

#include <QObject>

struct ItemStruct {
  QString item, img;
  int row, column;
};

class QSqlDatabase;

class Db : public QObject
{
  Q_OBJECT
public:
  explicit Db(QObject *parent = nullptr);


  QList<ItemStruct> getElements();

signals:

public slots:

private:
  QSqlDatabase *db;
  bool open(QString file);
  bool createTables();
  void populate();

};

#endif // DB_H
