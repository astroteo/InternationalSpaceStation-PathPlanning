#include "BreadthFirstPathPlanner.h"
#include "State.h"
#include "CostComparator.h"
#include <algorithm>


class OptimalFuelBreadthFirstPathPlanner :
                              public BreadthFirstPathPlanner
{
  public:
    OptimalFuelBreadthFirstPathPlanner(Map* map, vector<double> v_start, vector<double> v_goal = {0., 0., 0.} ) :
                                      BreadthFirstPathPlanner(map)
    {
      vector<double> pv_start(this->start.begin(),this->start.end());
      for(auto s : v_start )
        pv_start.push_back(s);

      State start_state_(pv_start);

      vector<double> pv_goal(this->goal.begin(),this->goal.end());
      for(auto g : v_goal )
        pv_goal.push_back(g);


      State goal_state_(pv_goal);

      this->start_state = start_state_;
      this->goal_state = goal_state_;
    }


    void do_job() override;




  public:
    //record(s)
    State start_state, goal_state;
    vector<vector<double>> impulses;
    //CostComparator optimal_fuel_comparator;


};
