#include "transformations.h"

void
to_3dtlib(vector<Point>& positions_3dt,
          vector<Point>& velocities_3dt,
          vector<state_type> trajectory)
{
  for(auto pt : trajectory )
  {
    Point p_3dt(pt[0],pt[1],pt[2]);
    Point v_3dt(pt[3],pt[4],pt[5]);
    positions_3dt.push_back(p_3dt);
    velocities_3dt.push_back(v_3dt);
  }

}
