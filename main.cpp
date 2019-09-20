#include <iostream>
#include <cstring> // string library
#include <cstdlib> // standard C library!!
#include <stdlib.h> // includes atoi
#include <thread>

#include "integration.h"
#include "visualization.h"
#include "transformations.h"
#include "3DTlib/math/matrix/matrix.h"
#include "KalmanFilter.h"
#include "simulation.h"
#include "auxiliary.h"


using namespace std;
using namespace _3dtlib;


int main(int argc, const char * argv[])
{
  cout << " OK => let's start" << endl;
  state_type x0(4);
   x0[0] = 10.0;
   x0[1]= 50;
   x0[2] = 0.01;
   x0[3] = 0;
  state_type y0(4);

  Matrixd P0({{2,0,0,0},
              {0,2,0,0},
              {0,0,0.1,0},
              {0,0,0,0.1}});

  Matrixd H({{1,0,0,0},
             {0,1,0,0}});

  Matrixd R({{1 ,0},
             {0, 1}});
            // 10 m error on position estimation
  Matrixd Q({{0,0,0,0},
             {0,0,0,0},
             {0,0,0,0},
             {0,0,0,0}});


  //convert trajectory to State
  vector<state_type> trajectory_an;

  Point x_(x0[0], x0[1],x0[2], x0[3]);
  double Dt = 20;
  double tt=0;
  double tt_c =0;
  Point p_initial(x0[0],x0[1]);

  // generate first measurement
  Point y_m = generate_measurement(p_initial,R);

  //initialize kf with initial state (from Ist measuremne)
  state_type assumed_initial_state{y_m.x(),y_m.y(),0,0};
  State s0(assumed_initial_state);

  //Instantiate Kf
  KalmanFilter kf(H,Q,R,P0,s0);

  //run simulation => measurement on posiition only
  while( tt < 4000)
  {
      State x_an = kf.A * x_;
      Point x_an_(x_an.get_elements()[0],x_an.get_elements()[1]);

      Dt = 4 * (float) (rand() % 10);
      kf.update(y_m, Dt);

      tt = tt + Dt;
      cout <<"Time Step" << Dt << endl;

      cout <<"Analytical propagation: "<< x_an << endl;
      cout <<"Measure: " << y_m <<"Estimate" << kf.x_hat <<endl;

      tt_c++;

      x_ = x_an;

      state_type x_v({x_an.get_elements()[0],
                      x_an.get_elements()[1],
                      x_an.get_elements()[2],
                      x_an.get_elements()[3]});

      trajectory_an.push_back(x_v);

      save_csv(tt, x_v, y_m, kf.x_hat, "result_2d.csv");
      y_m = generate_measurement(x_an_,R);

      }
      display_trajectory(trajectory_an);
}

/******************************************************************************/

/*

// solve ODE's problem,
  pair< vector<state_type>, vector<double>> Xt =
                                            propagate_2d(x0,
                                                        1e-17, 0, 200* 60);

   std::vector<state_type> trajectory = Xt.first;
  std::vector<double> times = Xt.second;

  KalmanFilter kf(H,Q,R,P0,s0);

  vector<state_type>::iterator traj_it = trajectory.begin();
  advance(traj_it,1);
  int t_i =1;

  while(traj_it != trajectory.end())
  {

    Point p_gt ((*traj_it)[0], (*traj_it)[1]);
    Point v_gt ((*traj_it)[2], (*traj_it)[3]);
    State gt(p_gt,v_gt);


    Point x__(trajectory[t_i-1][0], trajectory[t_i-1][1],trajectory[t_i-1][2], trajectory[t_i-1][3]);
    Point x_an = kf.A * x__;
    Point x_an_(x_an.x(),x_an.y());
    //Point y_m = generate_measurement(p_gt,R);
    Point y_m = generate_measurement(x_an_,R);


    double Dt = times[t_i] - times[t_i -1];
    kf.update(y_m, Dt);

    traj_it++;
    t_i++;
    cout <<"Time Step" << Dt << endl;

    cout <<"Analytical propagation: "<< x_an << endl;
    cout << "Ground truth: " << gt.p<<gt.v <<endl;
    cout <<"Measure: " << y_m <<"Estimate" << kf.x_hat <<endl;
  }
  display_trajectory(trajectory);
*/
