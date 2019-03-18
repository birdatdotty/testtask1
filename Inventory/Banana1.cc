#include "Banana1.h"

#include <QPair>

Banana1::Banana1()
  : ItemBase("banana", ":/fruit/banana", qMakePair(1,2), -1)
{

}

Banana1::Banana1(int n)
  : ItemBase("banana", ":/fruit/banana", qMakePair(1,2), n)
{

}
