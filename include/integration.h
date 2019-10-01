#include <boost/numeric/odeint.hpp>
using boost::numeric::odeint::runge_kutta4; // -> it's a template
using boost::numeric::odeint::integrate_const; // -> it's a template
using boost::numeric::odeint::integrate;



typedef std::vector<double> state_type;

const double omega = 0.00113;
const double omega_2 = pow(omega,2);


const double Ix = 0.3125;
const double Iy = 0.25;
const double Iz = 0.5;

void cholessy_wiltshire_2d(const state_type &x, state_type &dxdt,  double /* t */);
void euler(const state_type &x, state_type &dxdt,  double /* t */);
std::pair< std::vector<state_type>, std::vector<double> > propagate_2d( state_type x0,double dt, double Ti, double Tf);
std::vector<state_type>measure_2d( state_type x0, double dt, double Ti, double Tf);
void print_trajectory(std::vector<state_type> X);
