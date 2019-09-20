#include "integration.h"
#include "collection.h"

#include "3DTlib/math/matrix/rotation.h"
#include "3DTlib/math/angle.h"

using boost::numeric::odeint::runge_kutta4; // -> it's a template
using boost::numeric::odeint::integrate_const; // -> it's a template
using boost::numeric::odeint::integrate;

using namespace std;



void
print_trajectory( std::vector<state_type> X)
{
  for (auto x : X)
    cout << "x: " << x[0]<< " , y: "<<  x[1] << " z:" << x[2]
         << "vx: " << x[3]<< " , vy: "<<  x[4] << " , vz: "<<  x[5]<< endl;
}
void
cholessy_wiltshire_2d(const state_type &x,
                            state_type &dxdt,
                            double /* t */ )
{
  dxdt[0] = x[2];
  dxdt[1] = x[3];
  dxdt[2] = 3 * omega_2 * x[0] +
                          2 * omega * x[3];
  dxdt[3] =  -2 * omega * x[2];
}


void
euler(const state_type &x,
            state_type & dxdt,
            double /* t */)
{
  dxdt[0] = (1/Ix) * (Iz-Iy) * x[1] * x[2];
  dxdt[1] = (1/Iy) * (Iz-Ix) * x[2] * x[0];
  dxdt[2] = (1/Iz) * (Iy-Ix) * x[1] * x[0];

}

pair< vector<state_type>, vector<double> >
propagate_2d( state_type x0,
             double dt, double Ti, double Tf)
{
  vector <state_type> _X;
  vector <double> t;
  StateTimeCollector stc(_X,t);

  runge_kutta4<state_type> solver;

  size_t states = integrate(cholessy_wiltshire_2d,
                            x0, Ti, Tf, dt,
                            stc);

  cout << "<= Done!" << endl;

  vector<state_type> X;


  for (auto _x : _X)
  {
      state_type x = {_x[0],_x[1],.0,_x[2],_x[3],.0};
      X.push_back(x);
    }

  pair < vector<state_type>, vector<double> > Xt(X,t);
  return Xt;

}
