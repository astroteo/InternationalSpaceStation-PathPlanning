
#include "State.h"
Point
State::
get_p(void)
{ 
  return this->p;
}

Point
State::
get_v(void)
{
  return this->v;
}

std::vector<double>
State::
get_elements(void)
{
  return this->elements;
}
