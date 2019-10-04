#include <set>
#include <queue>
#include <utility>
#include "Map.h"
#include <tuple>
#include <numeric>

#ifndef __combine_cube_vertex
//#define __combine_cube_vertex true // SET CAREFULLY !! >8GB ram needed!!!
#endif


using namespace std;

typedef array<int,3> p_type;
typedef tuple<p_type,string> ap_type;// include tuple {i,j,k}

class BreadthFirstPathPlanner
{
  public:
    BreadthFirstPathPlanner(Map* map_) : mapper(map_){
      this->start = mapper->sP();
      this->goal =  mapper->gP();
      this->pos = this->start;

      //Fill actions map
      p_type up   = {0,0,1}; actions["u"] = up;
      p_type down = {0,0,-1};actions["d"] = down;
      p_type left = {-1,0,0};actions["l"] = left;
      p_type right= {1,0,0}; actions["r"] = right;
      p_type fwrd = {0,1,0}; actions["f"] = fwrd;
      p_type bwrd = {0,-1,0};actions["b"] = bwrd;

      //Create map adding combinations
      #ifdef __combine_cube_vertex
      for( auto a1 : actions)
      {
        for(auto a2 : actions)
        {
          p_type ac_point;
          double ac_point_norm = 0;
          for(int i=0; i<3; i++)
          {
            ac_point[i]= a1.second[i] + a2.second[i];
            ac_point_norm += a1.second[i] + a2.second[i];

          }

          string ac_name = a1.first + a2.first;

          if(ac_point_norm> 0 && actions.find(ac_name) ==actions.end())
          {

            sort(ac_name.begin(),ac_name.end());
            actions[ac_name] = ac_point;
          }
        }
      }

      #endif



    }


      //Actions:
      map<string,p_type> get_valid_actions(void);
      map<string,p_type> get_valid_actions(p_type ev_pos);
      void do_job(void);
      void save_trajectory(const string& path, double vis_intensity =0);



  public:
    //algorithm's container(s)
    Map* mapper;
    p_type pos,start,goal;
    set<p_type> visited_points;
    map<string,p_type> actions;

    //record(s)
    vector<string> controls;
    vector<p_type> p_trajectory;
    vector<vector<double>> trajectory;



};
