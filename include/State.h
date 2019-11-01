#ifndef __STATE__
#define __STATE__


#include "3DTlib/math/point.h"
#include "3DTlib/math/matrix/matrix.h"

using namespace _3dtlib;
using namespace std;

class State : public Matrixd
{
public:

  State(){};

  State( vector<double> pv)
  {
    if(pv.size() > 4)
    {
      Point _v(pv[3],pv[4],pv[5]);
      Point _p(pv[0],pv[1],pv[2]);
      this->v = _v;
      this->p = _p;
      rows = 6;
      cols = 1;
    }
    else
    {
      Point _v(pv[2],pv[3]);
      Point _p(pv[0],pv[1]);
      this->v = _v;
      this->p = _p;
      rows = 4;
      cols = 1;
    }

    for(double pvi : pv)
      elements.push_back(pvi);


  }

  State(Point p_, Point v_)
  {
    p = p_;
    v = v_;
    rows = 4;
    cols = 1;

    this->elements.push_back(p_[0]);
    this->elements.push_back(p_[1]);
    if(p_.c() > 2 || p_.r() > 2)
    {
      this->elements.push_back(p_[2]);
      rows = 6;
    }

    this->elements.push_back(v_[0]);
    this->elements.push_back(v_[1]);
    if(v_.c() > 2 || v_.r() > 2)
      this->elements.push_back(v_[2]);


  }

  State(const Matrix<double>& M)
      :
    Matrix<double> (M) {};
  /*
  State operator+(State lhs, const& State rhs)
  {
    for(int i=0; i<lhs.size(); i++)
    {
      lhs[i] += rhs[i]
    }
  }
  */
  //TODO: change method names to p(), v()
  Point get_p(void);
  Point get_v(void);
  std::vector<double> get_elements(void);

public://TODO: change name v->vel, p->pos
       //TODO: make p,v protected
  Point v;
  Point p;
};
#endif
