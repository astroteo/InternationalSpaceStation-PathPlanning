#include <iostream>
#include <cstring> // string library
#include <cstdlib> // standard C library!!
#include <stdlib.h> // includes atoi
#include <thread>

#include "3DTlib/math/matrix/matrix.h"
#include "3DTlib/math/point.h"

#include <boost/algorithm/string.hpp>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/octree/octree_search.h>


#include <gtest/gtest.h>
#include "Tester.h"

using namespace std;
using namespace _3dtlib;

typedef vector<double> ptype;

class Node // Difficult to create a map of nodes
{
  public:
    Node(pcl::PointXYZI p_) : up(nullptr),down(nullptr), left(nullptr),right(nullptr)
  {
    this->p.push_back(p_.x);
    this->p.push_back( p_.y);
    this->p.push_back( p_.z);
    this->free = p_.intensity > 0 ? true : false;

  }

  ~Node(){}


  public:
    ptype p;
    bool free;
    Node *up, *down, *left, *right;
    bool is_goal = false;

  };

void read_cloud(const std::string& cloud_file,pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
template <typename T> std::vector<T> linspace(T a, T b, size_t N);
void save_map(const std::string& map_path, pcl::PointCloud<pcl::PointXYZI>::Ptr cloud);

int main(int argc, const char* argv[])
{
  double voxel_size = .5;
  double cube_size = .5;
  /*('max dims:', 58.64746, 24.784914, 55.6514)
  ('min dims:', -25.899393, -18.903086, -55.6514)*/
  double minx = -25.899393;
  double miny = -18.903086;
  double minz =  -55.6514;

  double maxx =  58.64746;
  double maxy = 24.784914;
  double maxz = 55.6514;
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


  vector< vector< vector<int> > > int_grid;
  //grid.reserve((int) 120/cube_size);

  for(int i=0; i< lx.size(); i++ )
  {
    vector< vector<int> > yz_span;
    for(int j=0; j< ly.size(); j++)
    {
      vector<int> z_span;
      for(int k=0; k< lz.size(); k++)
      {
        z_span.push_back(0);
      }
      yz_span.push_back(z_span);

    }
    int_grid.push_back(yz_span);
  }

  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

  cout <<"x-span: "<< int_grid.size()
       <<"y-span: "<< int_grid[0].size()
       <<"z-span: "<< int_grid[0][0].size() << endl;

    cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

  vector< vector< vector<pcl::PointXYZI> > > map;
  //create map
  for(int i=0; i< lx.size(); i++ )
  {
    double _x = lx[i];

    vector< vector<pcl::PointXYZI> > yz_span;
    for(int j=0; j< ly.size(); j++)
    {
      double _y = ly[j];

      vector<pcl::PointXYZI> z_span;
      for(int k=0; k< lz.size(); k++)
      {
        double _z = lz[k];

        pcl::PointXYZI pp;
        pp.x = _x; pp.y = _y; pp.z = _z;
        pp.intensity = 0.;

        if(iss_octree.isVoxelOccupiedAtPoint(_x,_y,_z))
          {
            pp.intensity = 1.;
            cube_pcl->push_back(pp);// ISS-pcl reshaped => check into C.C.
          }

        z_span.push_back(pp);//grid[i][j][j] = (int)pp.intensity;
      }
      yz_span.push_back(z_span);
    }
    map.push_back(yz_span);
  }

  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
  cout<< "occupied-points #- " << cube_pcl->size()<< endl;
  save_map("../MAPs/iss_map_pcl.csv",cube_pcl);

  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

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
save_map(const std::string& map_path, pcl::PointCloud<pcl::PointXYZI>::Ptr cloud)
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
