#include "State.h"

/*

The following ΔV computation is implemented:

*/

struct CostComparator
{
  State propagate_trajectory(State s0, State s1, double n =  0.00113)
  {
      double dt = 1;

      Matrixd Arr = {{4 - 3 * cos(n * dt), 0},
                     {6 *( sin(n * dt) - n *dt ),1}};

      Matrixd Arv = {{(1/n)  * sin(n * dt), (2 / n) * (1 - cos(n * dt)) },
                     {(2 /n) * (cos(n * dt) -1), (1 / n) * (4 * sin(n*dt) - 3 * n *dt)}};

      Matrixd Avr = {{3 * n * sin(n * dt), 0},
                     {6 * n *(cos(n * dt) -1),0}};

      Matrixd Avv= {{cos(n * dt), 2 *sin(n * dt)},
                    {-2 * sin(n * dt),4*cos(n * dt) - 3}};

      Matrixd Acw(6,6);


      for (int i = 0; i < 6;  i++)
      {
        for (int j = 0; j < 6; j++)
        {

          if (i < 3 & j < 3)
            Acw(i,j) = Arr(i,j);
          else if( i < 3 & j >= 3)
            Acw(i,j) = Arv(i,j-2);
          else if ( i >=  3 & j < 3)
            Acw(i,j) = Avr(i-3,j);
          else if ( i>= 3 & j>= 3)
            Acw(i,j) = Avv(i-3,j-3);
        }
      }


    return s0;
  }


};
