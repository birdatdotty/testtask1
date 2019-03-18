#include "Apple1.h"

#include <QPair>

Apple1::Apple1()
  : ItemBase ("apple", ":/fruit/apple", qMakePair(1,1), -1)
{

}

Apple1::Apple1(int n)
  : ItemBase("apple", ":/fruit/apple", qMakePair(1,1), n)
{

}
