#include <set>
#include <queue>
#include <utility>
#include "Map.h"
#include <tuple>

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

    };

    //Actions:
    map<string,p_type> get_valid_actions(void);
    map<string,p_type> get_valid_actions(p_type ev_pos);
    void do_job(void);
    void save_trajectory(const string& path, double vis_intensity =0);



  public:
    Map* mapper;
    p_type pos,start,goal;
    set<p_type> visited_points;
    map<string,p_type> actions;

    //
    vector<string> controls;
    vector<p_type> p_trajectory;
    vector<vector<double>> trajectory;



};
