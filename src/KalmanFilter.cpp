#include "KalmanFilter.h"

void
KalmanFilter::update_cw_dynamic (double dt)
{
  Matrixd Arr = {{4 - 3 * cos(n * dt), 0},
                 {6 *( sin(n * dt) - n *dt ),1}};

  Matrixd Arv = {{(1/n)  * sin(n * dt), (2 / n) * (1 - cos(n * dt)) },
                 {(2 /n) * (cos(n * dt) -1), (1 / n) * (4 * sin(n*dt) - 3 * n *dt)}};

  Matrixd Avr = {{3 * n * sin(n * dt), 0},
                 {6 * n *(cos(n * dt) -1),0}};

  Matrixd Avv= {{cos(n * dt), 2 *sin(n * dt)},
                {-2 * sin(n * dt),4*cos(n * dt) - 3}};

  Matrixd Acw(4,4);


  for (int i = 0; i < 4;  i++)
  {
    for (int j= 0; j < 4; j++)
    {

      if (i < 2 & j < 2)
        Acw(i,j) = Arr(i,j);
      else if( i < 2 & j >= 2)
        Acw(i,j) = Arv(i,j-2);
      else if ( i >=  2 & j < 2)
        Acw(i,j) = Avr(i-2,j);
      else if ( i>= 2 & j>= 2)
        Acw(i,j) = Avv(i-2,j-2);
    }
  }


  this->A = Acw;
}

State
KalmanFilter::predict(Point y,double dt)
{
  return  H * y;
}

void
KalmanFilter::update(Point y,double dt)
{

  // Compure Error matrices
  Matrixd Sl = H * P * H.t();
  Matrixd K_prev = P * H.t() * ( H * P * H.t() + R).inv();

  //compute state transition matrix
  update_cw_dynamic(dt);

  //Update
  x_hat_new = A * x_hat;
  P = A * P * A.t() + Q;

  //compute Gain
  Matrixd K = P * H.t() * ( H * P * H.t() + R).inv();

  //Innovation
  x_hat_new += K * (y - H * x_hat_new);

  // refresh
  P = ( I - K * H) * P;
  x_hat = x_hat_new;

  estimates.push_back(x_hat);

}

/******************************************************************************/
/*
K = P*C.transpose()*(C*P*C.transpose() + R).inverse();
x_hat_new += K * (y - C*x_hat_new);
P = (I - K*C)*P;
x_hat = x_hat_new;
*/
/******************************************************************************/
