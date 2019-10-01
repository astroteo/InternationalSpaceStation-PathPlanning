#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <vector>
#include <array>

using namespace std;

typedef vector< vector< vector<pcl::PointXYZI> > > grid_type;

class Map
{

 public:
   Map(double tbox_size,double bbox_size, double el_size)
   {

     int N = (int)ceil((tbox_size-bbox_size)/el_size);
     vector< vector< vector<pcl::PointXYZI>>> grid_;
     // Loop for iniziale the Map. TODO: find smarter way
     for(unsigned int i=0; i< N; i++)
     {
       vector<vector<pcl::PointXYZI>> vyz;

       for (unsigned int j=0; j< N; j++)
       {
        vector<pcl::PointXYZI> vz;

         for(unsigned int j=0; j< N; j++)
         {
           pcl::PointXYZI p0;
           vz.push_back(p0);

         }
         vyz.push_back(vz);
       }

       this->grid.push_back(vyz);
     }

     cout << this->grid.size()<<" "
          << this->grid[0].size()<<" "
          << this->grid[1].size()<< " "<<endl;
     this->el_size = el_size;
     this->tbox_size = tbox_size;
     this->bbox_size =bbox_size;


     //Starting-Point idx
     is=0;js=0;ks=0;

     //GoalPoint idx
    ig=0;jg=0;kg=0;

    //Set dim as attribute
    this->N = N;

   };
   ~Map(){};

   void insert_point(pcl::PointXYZI pp,int i, int j, int k);
   void set_start(int i, int j, int k);
   void set_goal(int i, int j, int k);
   array<int,3> sP(void);
   array<int,3> gP(void);
   bool is_free(array<int,3> pg);
   bool is_free(double x, double y, double z);
   void set_start(double x, double y, double z);
   void set_goal(double x, double y, double z);
   array<int,3> get_idxs(double x, double y, double z);
   vector<double> at(int i, int j, int k);
   pcl::PointXYZI pcl_at(int i, int j, int k);


 public:
     grid_type grid;
     double el_size, tbox_size, bbox_size;
     int is,js,ks,ig,jg,kg;
     int N;


};
