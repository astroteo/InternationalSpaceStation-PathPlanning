#include <set>
#include <queue>
#include <utility>
#include "Map.h"
#include <tuple>
#include <numeric>

#ifndef __combine_cube_vertex
#define __combine_cube_vertex true // SET CAREFULLY !! >8GB ram needed!!!
#endif


using namespace std;

typedef array<int,3> p_type;
typedef tuple<p_type,string> ap_type;// include tuple {i,j,k}
typedef tuple<p_type,string,double> ap_astar_type;

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

      for(auto a1:actions)
      {
        for(auto a2: actions)
        {
          if(a1.first != a2.first && a1.first.length() == 1 && a2.first.length() == 1)
          {
            string ac = a1.first + a2.first;
            sort(ac.begin(),ac.end());

            bool coaxial_flag = true;
            double tt = 0;
            p_type sa,ap;
            for(int i=0; i<3; i++)
              ap[i] = a1.second[i] + a2.second[i];

            int cnt_ones=0;
            for(auto v:ap)
            { if(abs(v)==1)
                cnt_ones += 1;

            }

            if(cnt_ones == 2 && actions.find(ac) == actions.end())
              actions[ac]  = ap;

          }
        }
      }


      cout << "...evaulating #-" << actions.size()<< " possible actions" <<endl;
      #endif

    }


      //Actions:
      map<string,p_type> get_valid_actions(void);
      map<string,p_type> get_valid_actions(p_type ev_pos);
      virtual void do_job(void);
      void save_trajectory(const string& path, double vis_intensity =0);



  public:
    //algorithm's container(s)
    Map *mapper;
    p_type pos,start,goal;
    set<p_type> visited_points;
    map<string,p_type> actions;

    //record(s)
    vector<string> controls;
    vector<p_type> p_trajectory;
    vector<vector<double>> trajectory;

};
