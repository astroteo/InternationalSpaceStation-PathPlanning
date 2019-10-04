#ifndef __STATE__
#define __STATE__


#include "3DTlib/math/point.h"
#include "3DTlib/math/matrix/matrix.h"

using namespace _3dtlib;
using namespace std;

class State : public Matrixd
{
public:
  State( vector<double> pv)
  {
    if(pv.size() > 4)
    {
      Point _v(pv[3],pv[4],pv[5]);
      Point _p(pv[0],pv[1],pv[2]);
      this->v = _v;
      this->p = _p;
    }
    else
    {
      Point _v(pv[2],pv[3]);
      Point _p(pv[0],pv[1]);
      this->v = _v;
      this->p = _p;
    }

    for(double pvi : pv)
      elements.push_back(pvi);

    rows = 6;
    cols = 1;
  }

  State(Point p_, Point v_)
  {
    p = p_;
    v = v_;
    this->elements.push_back(p_[0]);
    this->elements.push_back(p_[1]);
    this->elements.push_back(v_[0]);
    this->elements.push_back(v_[1]);
  }

  State(const Matrix<double>& M)
      :
    Matrix<double> (M) {};

  Point get_p(void);
  Point get_v(void);
  std::vector<double> get_elements(void);

public:
  Point v;
  Point p;
};
#endif
