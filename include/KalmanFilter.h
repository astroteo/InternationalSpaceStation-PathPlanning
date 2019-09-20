#include "State.h"
#include <math.h>


using namespace _3dtlib;
using namespace std;

const double n = 0.00113;

class KalmanFilter
{

public:
  KalmanFilter(const Matrixd& H_,const Matrixd& Q_,const Matrixd& R_,
               Matrixd& P0, State& x0)
        :
        H(H_),Q(Q_), R(R_),
        P(P0), x_hat(x0), x_hat_new(x0)
  {
   this->update_cw_dynamic(1e-12);
  }
  KalmanFilter(Matrixd A_ , const Matrixd& H_ ,const Matrixd& Q_,const Matrixd& R_,
               Matrixd& P0, State& x0)
        :
        A(A_),
        H(H_),Q(Q_), R(R_),
        P(P0), x_hat(x0),x_hat_new(x0)
  {
    }


 public:
  void update_cw_dynamic(double dt = 0.1);
  State predict(Point y, double dt = 0.1);
  void update(Point y,double dt = 0.1);

  public:
   State& x_hat, x_hat_new;
   Matrixd& P;
   Matrixd A;
   const Matrixd H, Q, R;
   const Matrixd I = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};

   vector<State> estimates;

};
