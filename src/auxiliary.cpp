#include "auxiliary.h"
void
save_csv(double t, Point ground_truth, Point measurement, State filter, std::string filename)
{
  if (std::ifstream(filename) && flag_init_record)
  {
     std::cout << "File already exists" << std::endl;
     int rm = std::remove(filename.c_str());
     flag_init_record = false;

   }
  std::ofstream result_file;
  std::vector<double> v = filter.get_elements();
  result_file.open(filename,std::ofstream::out | std::ofstream::app);

  double px = v[0];
  double py = v[1];
  double vx = v[2];
  double vy = v[3];

  result_file << t
              <<","<< ground_truth.x() << "," << ground_truth.y()<<","
              <<measurement.x() << ", "<< measurement.y()  << ","
              << px << "," << py <<","
              << vx << "," << vy << std::endl;

  //result_file << std::endl;
  result_file.close();
}

void
save_csv(double t, vector<double> ground_truth, Point measurement, State filter, std::string filename)
{
  std::ofstream result_file;
  std::vector<double> v = filter.get_elements();
  if (std::ifstream(filename) && flag_init_record)
  {
     std::cout << "File already exists" << std::endl;
     int rm = std::remove(filename.c_str());
     flag_init_record = false;

   }

  result_file.open(filename,std::ofstream::out | std::ofstream::app);



  double px = v[0];
  double py = v[1];
  double vx = v[2];
  double vy = v[3];

  result_file << t  <<","
              << ground_truth[0] << "," << ground_truth[1]<<","
              << ground_truth[2] << "," << ground_truth[3]<<","
              <<measurement.x() << ", "<< measurement.y()  << ","
              << px << "," << py <<","
              << vx << "," << vy << std::endl;

  //result_file << std::endl;
  result_file.close();
}
