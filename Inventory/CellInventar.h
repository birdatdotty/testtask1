#ifndef CELLINVENTAR_H
#define CELLINVENTAR_H

#include "CellBase.h"

class Inventar1;
class Inventory1;

class CellInventar : public CellBase
{
  public:
    CellInventar(ItemBase* item, QPair<int,int> part, Inventory1* inventory1, QWidget* parent = nullptr);
    bool isFree();
    bool testType(QString type);

  protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

  private:
    Inventory1* inventory1;
};

#endif // CELLINVENTAR_H
