#include "Banana.h"

#include <QPair>

Banana::Banana()
  : Item("banana", ":/fruit/banana", qMakePair(1,2), -1)
{

}

Banana::Banana(int n)
  : Item("banana", ":/fruit/banana", qMakePair(1,2), n)
{

}
