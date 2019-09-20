#include "simulation.h"



Point
generate_measurement(Point y_gt, const Matrixd R)
{
  double dx = (double) (rand() % 20) - 10;
  double dy = (double) (rand() % 20) - 10;
  Point err (1 * dx , 1 * dy);
  Point x_measure = y_gt + R * err;

  return x_measure;

}
