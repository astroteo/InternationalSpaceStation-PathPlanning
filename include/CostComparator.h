#include "State.h"
#include "integration.h"
#include "cmath"
/*

The propagation for tau = 1s is implemented
the closest point depending on the 'action'(a.k.a) next state
is considered

*/

struct CostComparator
{

  public:
    CostComparator(){

      State s_init(0,0,0,0,0,0);
      this->initial_state = s_init;

      };
    CostComparator(State s_init){

      this->initial_state = s_init;

    };

    /*
    propagate trajectory over a fixed time step.
    */

    State propagate_trajectory(State si, double tau = 1.)
    {
        double Ct = cos(omega * tau);
        double St = sin(omega * tau);

        Matrixd Phi = {{  4-3*Ct,            0,            0,           St/omega,             2/omega*(1-Ct),        0     },
                       {  6*(St-omega*tau),  1,            0,    -2/omega*(1-Ct), 1/omega*(4*St-3*omega*tau),        0     },
                       {  0,                 0,           Ct,                  0,                          0,   1/omega*St },
                       {  3*omega*St,        0,            0,                 Ct,                       2*St,        0     },
                       { -6*omega*(1-Ct),    0,            0,              -2*St,                     4*Ct-3,        0     },
                       {  0              ,   0,    -omega*St,                  0,                          0,        Ct    }};

        State sf = Phi * si;

        return sf;
    }

    /*
    propagate until get out of current grid or time is exceeded.
    TODO: pass el_size, tmax, dt via constructor
    */
    State next_state( State si, double el_size = .5, double tmax = 10., double dt = 0.5)
    {
      double tau = dt;
      bool out_of_grid = false;

      State sf = propagate_trajectory(si,tau);

      while( tau < tmax && !out_of_grid )
      {
        sf = propagate_trajectory(si,tau);


        if( ((State) (sf - si)).pnorm() >= sqrt(2) * el_size)
          out_of_grid = true;

        tau += dt;
      }

      return sf;

    }


    /*Comparator comparing two possible final states
      TODO: check what type of point type is considered in PathPlanner!!
    */
    bool operator ()(const State& fp1, const State& fp2)
    {
       State ns = next_state(this->initial_state);

       if (((State)( ns - fp1 )).pnorm()
                           >=
           ((State)( ns - fp2 )).pnorm())
       {
         return true;
       }
       else
       {
         return false;
       }
    }

  public:
    State initial_state;

  protected:
    double omega = 0.00113;


};
