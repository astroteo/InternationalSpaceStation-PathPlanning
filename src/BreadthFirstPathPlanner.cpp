#include "BreadthFirstPathPlanner.h"
#ifndef __dbg
//#define __dbg true
#endif

map<string,p_type>
BreadthFirstPathPlanner::get_valid_actions()
{
  map<string,p_type> valid_actions;
  for(auto a : actions)
  {
    p_type pg ={ this->pos[0] + a.second[0],
                 this->pos[1] + a.second[1],
                 this->pos[2] + a.second[2]};

    if(mapper->is_free(pg) > 0)
      valid_actions[a.first] = pg;
  }
  return valid_actions;
}

map<string,p_type>
BreadthFirstPathPlanner::get_valid_actions(p_type ev_pos)
{
  map<string,p_type> valid_actions;
  for(auto a : actions)
  {
    p_type pg ={ ev_pos[0] + a.second[0],
                 ev_pos[1] + a.second[1],
                 ev_pos[2] + a.second[2]};

    if(mapper->is_free(pg))
      valid_actions[a.first] = a.second;
  }
  return valid_actions;
}

void
BreadthFirstPathPlanner::do_job(void)
{
  queue<p_type>  q;
  set<p_type> visited;
  map<p_type,ap_type> goal_branch;

  bool path_found = false;

  q.push(this->start);


  cout<< "starting path computation ..."<<endl;

  //Path planner
  while (!q.empty())
  {
    p_type pt = q.front();
    q.pop();

    #ifdef __dbg
    cout << "iterating==> " << endl
        << "root-node:"<<pt[0]<<","<<pt[1]<<"," <<pt[2]<<endl;
    #endif

    if(pt == goal)
    {
      cout << "... path successfully computed" << endl;
      path_found = true;
      break;
    }

    #ifdef __dbg
    cout << "#-valid-actions: " << get_valid_actions(pt).size() << endl;
    #endif

    for(auto a : get_valid_actions(pt))
    {


      p_type p_next = {pt[0] + a.second[0],
                       pt[1] + a.second[1],
                       pt[2] + a.second[2]};

      #ifdef __dbg
      cout << "actions-->WTF:"<< a.second[0]
                              <<"," << a.second[1]
                              << "," << a.second[2]<<endl;
      cout << "Next point:"<< p_next[0]
                              <<"," << p_next[1]
                              << "," << p_next[2]<<endl;
      #endif

      if (visited.find(p_next) == visited.end())
      {
        visited.insert(p_next);
        q.push(p_next);
        goal_branch[p_next] = make_tuple(pt,a.first);
      }
    }
  }

  //recostruct trajectory & actions
  p_type curr_p = goal;
  p_trajectory.push_back(curr_p);
  controls.push_back("break");

  //accessing map[previos] = next
  p_type prv_p;// = std::get<0>(goal_branch[curr_p]);
  string ctrl;//  = std::get<1>(goal_branch[curr_p]);
  vector<string> controls_;
  while( std::get<0>(goal_branch[curr_p]) != this->start)
  {
     prv_p = std::get<0>(goal_branch[curr_p]);
     ctrl  = std::get<1>(goal_branch[curr_p]);

    controls_.push_back(ctrl);
    p_trajectory.push_back(prv_p);

    curr_p = prv_p;
  }

  //get flipped trajectory accessing positions
  std::vector<string>::iterator pctrl = controls_.end();
  for(auto p_idxs = p_trajectory.end(); p_idxs != p_trajectory.begin()++; --p_idxs)
  {
    p_type idxs = *p_idxs;
    vector<double> tp = mapper->at(idxs[0],idxs[1],idxs[2]);
    trajectory.push_back(tp);
    controls.push_back(*pctrl);
    pctrl--;

  }
    //trajectory.push_back((double) this->mapper)


}

void
BreadthFirstPathPlanner::save_trajectory(const string& path, double vis_intensity)
{
  ofstream traj_file;
  traj_file.open(path);
  traj_file.precision(17);

  for(auto p : this->trajectory)
  {
    traj_file << p[0] << ","<<
                 p[1] << ","<<
                 p[2];
    if(vis_intensity)
    {
      traj_file<< ","<< vis_intensity << endl;
    }
    else
    {
      traj_file << endl;
    }
  }

  traj_file.close();
}
