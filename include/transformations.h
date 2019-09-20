#include "3DTlib/math/point.h"
#include "3DTlib/math/matrix/rotation.h"
#include "3DTlib/math/angle.h"
/*
class State
{
public:
  State()
    :
    px(0),
    py(0),
    pz(0.0),
    vx(0.0),
    vy(0.0),
    vz(0.0),
    to_use(true) {};

  double px;
  double py;
  double pz;
  double vx;
  double vy;
  double vz;
  bool   to_use;
};
*/

using namespace std;
using namespace _3dtlib;
typedef std::vector<double> state_type;

void to_3dtlib(vector<Point>& trajectory_3dt,vector<Point>& velocities_3dt, vector<state_type> trajectory);
