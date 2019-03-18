#include "Apple.h"

#include <QPair>

Apple::Apple()
  : Item("apple", ":/fruit/apple", qMakePair(1,1), -1)
{

}

Apple::Apple(int n)
  : Item("apple", ":/fruit/apple", qMakePair(1,1), n)
{

}
