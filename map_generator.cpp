#include <iostream>
#include <cstring> // string library
#include <cstdlib> // standard C library!!
#include <stdlib.h> // includes atoi
#include <thread>
#include <fstream>

// Builtin classes
#include "BreadthFirstPathPlanner.h"

// 3dtlib
#include "3DTlib/math/matrix/matrix.h"
#include "3DTlib/math/point.h"

// Boost
#include <boost/algorithm/string.hpp>

// Pcl
#include <pcl/octree/octree_search.h>



#include <gtest/gtest.h>
#include "Tester.h"

using namespace std;
using namespace _3dtlib;

typedef vector<double> ptype;

void read_cloud(const std::string& cloud_file,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
template <typename T> std::vector<T> linspace(T a, T b, size_t N);
void save_cloud(const std::string& map_path, pcl::PointCloud<pcl::PointXYZI>::Ptr cloud);


/*
TEST(CheckIfPointsFree, StartAndGoalTest){
  ASSERT_TRUE(checkFreePoints(&map))
}*/

int main(int argc, const char **argv)
{
  // map-properties
  double voxel_size = .5;
  double cube_size = .5;
  double cube_length = 60.;
  /*('max dims:', 58.64746, 24.784914, 55.6514)
  ('min dims:', -25.899393, -18.903086, -55.6514)*/

  double sx =-20.735580;double sy = 5.788168; double sz = 4.799811;
  double gx = 10.735580;double gy =  -15.788168; double gz = -4.799811;
  //double gx =58.393463; double gy = 8.986570; double gz = -40.299297;


  cout << " create map from ISS pcl" << endl;

  pcl::PointCloud<pcl::PointXYZ>::Ptr iss_pcl(new
                                              pcl::PointCloud<pcl::PointXYZ>);
  std::string cpath = "../CADs/iss_pcl.csv";
  read_cloud(cpath,iss_pcl);

  pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> iss_octree((float)
                                                                  voxel_size);
  iss_octree.setInputCloud(iss_pcl);
  iss_octree.addPointsFromInputCloud();


  //define control cube:
  pcl::PointCloud<pcl::PointXYZI>::Ptr cube_pcl(new
                                               pcl::PointCloud<pcl::PointXYZI>);

  vector<double> lx = linspace(-60.,60.,(int) 120/cube_size);
  vector<double> ly = linspace(-60.,60.,(int) 120/cube_size);
  vector<double> lz = linspace(-60.,60.,(int) 120/cube_size);

  Map map(60,-60,cube_size);
  cout << "MAP instantiated" << std::endl;

  //create  Map => TODO: to incorporate into fucntion belonging to Map
  for(int i=0; i< lx.size(); i++ )
  {
    double _x = lx[i];

    for(int j=0; j< ly.size(); j++)
    {
      double _y = ly[j];

      for(int k=0; k< lz.size(); k++)
      {
        double _z = lz[k];

        pcl::PointXYZI pp;
        pp.x = _x; pp.y = _y; pp.z = _z;
        pp.intensity = 0.;

        if(iss_octree.isVoxelOccupiedAtPoint(_x,_y,_z))
          {
            pp.intensity = 1.;

          }

        if( i==0           ||  j ==0          ||  k ==0 ||
            i==lx.size()-1 ||  j==lx.size()-1 ||  k==lx.size()-1)
          {
            pp.intensity = .1;//Set to 1 => C.C. check with double coloe
          }

        if (pp.intensity > 0.)
            cube_pcl->push_back(pp);// ISS-pcl reshaped => check into C.C.

          map.insert_point(pp,i,j,k);

      }
    }
  }

  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
  cout<< "occupied-points #- " << cube_pcl->size()<< endl;
  save_cloud("../MAPs/iss_map_pcl.csv",cube_pcl);

  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

  //Path-Planning:
  map.set_start(sx,sy,sz);
  map.set_goal(gx,gy,gz);


  BreadthFirstPathPlanner bfs(&map);
  bfs.do_job();
  bfs.save_trajectory("../MAPs/path_planned_2.csv");

  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
  bool collision_flag = false;
  for(auto tp: bfs.trajectory)
  {
    //cout << tp[0] << ","<< tp[1] << ","<< tp[2]<<endl;;
    if(tp[0]> 0 && tp[1]> 0  && tp[2]> 0  )
      collision_flag = map.is_free((double)tp[0],(double)tp[1],(double)tp[2]);
  }
  if(!collision_flag)
    cout << "no collision occurred"<<endl;

  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

  //////////////////////////////////////////////////////////////////////

}

template <typename T>
std::vector<T>
linspace(T a, T b, size_t N)
{
    T h = (b - a) / static_cast<T>(N-1);
    std::vector<T> xs(N);
    typename std::vector<T>::iterator x;
    T val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h)
        *x = val;
    return xs;
}

void
read_cloud(const std::string& cloud_file, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
  std::ifstream infile(cloud_file);
  std::string line;

  while(std::getline(infile, line))
    {
      std::vector<string> pts;
      boost::split(pts, line, [](char c){return c == ' ';});

      pcl::PointXYZ pp;
      pp.x =  stod(pts[0]);
      pp.y =  stod(pts[1]);
      pp.z =  stod(pts[2]);
      cloud->push_back(pp);
    }

    cout << "read cloud from file: " << cloud_file << "#- " << cloud->size()
         << " points " << endl;
  }

void
save_cloud(const std::string& map_path, pcl::PointCloud<pcl::PointXYZI>::Ptr cloud)
{
    ofstream map_file;
    map_file.open(map_path);
    map_file.precision(17);

    for(auto p : cloud->points)
      map_file << p.x << ","<<
                  p.y << ","<<
                  p.z << ","<<
                  p.intensity << endl;

    map_file.close();

  }
