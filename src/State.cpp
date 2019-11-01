
#include "State.h"
Point
State::
get_p(void)
{
  if( this->elements.size() > 4)
  {
    Point p_(this->elements[0],
             this->elements[1],
             this->elements[2]);

    this->p = p_;

  }
  else
  {
    Point p_(this->elements[0],
             this->elements[1]);

    this->p = p_;
  }


  return this->p;
}

Point
State::
get_v(void)
{
  if( this->elements.size() > 4)
  {
    Point v_(this->elements[3],
             this->elements[4],
             this->elements[5]);

    this->v = v_;
  }
  else
  {
    Point v_(this->elements[2],
             this->elements[3]);
    this->v = v_;
  }

  return this->v;
}

std::vector<double>
State::
get_elements(void)
{
  return this->elements;
}
