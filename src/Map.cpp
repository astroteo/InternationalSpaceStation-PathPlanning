#include "Map.h"

void
Map::insert_point(pcl::PointXYZI pp, int i, int j, int k)
{

  this->grid[i][j][k] = pp;
}

void
Map::set_start(int i, int j, int k)
{
  this->is=i;
  this->js=j;
  this->ks=k;
}

void
Map::set_goal(int i, int j, int k)
{
  this->ig=i;
  this->jg=j;
  this->kg=k;
}

void
Map::set_start(double x, double y, double z)
{
  array<int,3> pt = this->get_idxs(x,y,z);
  this->is=pt[0];
  this->js=pt[1];
  this->ks=pt[2];
}

void
Map::set_goal(double x, double y, double z)
{
  array<int,3> pt = this->get_idxs(x,y,z);

  this->ig=pt[0];
  this->jg=pt[1];
  this->kg=pt[2];
}

array<int,3>
Map::sP(void)
{
  array<int,3> a;
  a[0] = this->is;
  a[1] = this->js;
  a[2] = this->ks;
  return a;
}

array<int,3>
Map::gP()
{
  array<int,3> a;
  a[0] = this->ig;
  a[1] = this->jg;
  a[2] = this->kg;

  return a;
}

vector<double>
Map::at(int i, int j, int k)
{
  pcl::PointXYZI pc = this->grid[i][j][k];
  vector<double> pos = {pc.x,pc.y,pc.z};
  return pos;
}

pcl::PointXYZI
Map::pcl_at(int i, int j, int k)
{
    pcl::PointXYZI pc = this->grid[i][j][k];
    return pc;
}

/* TODO: create grid from input cloud
void
Map::create_from_cloud(pcl::PointXYZI cloud)
{

}
*/

bool
Map::is_free(array<int,3> pg)
{
  bool free;
  if(pg[0] > this->grid.size() && pg[0] >0
          &&
     pg[1] > this->grid[0].size() && pg[1] >0
          &&
     pg[2] > this->grid[0][0].size() && pg[2] >0 )
  {

    free = false;
  }
  else
  {
    pcl::PointXYZI ppg = this->grid[pg[0]][pg[1]][pg[2]];
    if(ppg.intensity > 0.0001)
    {
      free = false;
    }
    else
    {
      free = true;
    }
  }
  return free;
}

array<int,3>
Map::get_idxs(double x, double y, double z)
{
  int i_ = (int) round((x - bbox_size) / el_size);
  int j_ = (int) round((y - bbox_size) / el_size);
  int k_ = (int) round((z - bbox_size) / el_size);

  array<int,3> v = {i_,j_,k_};

  return v;
}


bool
Map::is_free(double x, double y, double z)
{
  int i_ = (int) ceil((x + el_size -bbox_size) /el_size);
  int ip = (int) floor((x - el_size -bbox_size) /el_size);

  int j_ = (int) ceil((y + el_size -bbox_size) /el_size);
  int jp = (int) floor((y - el_size -bbox_size) /el_size);

  int k_ = (int) ceil((z + el_size -bbox_size) /el_size);
  int kp = (int) floor((z - el_size -bbox_size) /el_size);

  array<int,3> pg1 = {i_,j_,k_};array<int,3> pg3 = {ip,jp,k_};
  array<int,3> pg2 = {ip,j_,k_};array<int,3> pg4 = {ip,jp,kp};
  array<int,3> pg5 = {i_,jp,k_};array<int,3> pg6 = {ip,j_,kp};
  array<int,3> pg7 = {ip,j_,k_};array<int,3> pg8 = {i_,j_,kp};

  //auto vpg = [=](array<int,3> pg)->bool{return this->is_free(pg);};
  bool free;
  if(this->is_free(pg1) && this->is_free(pg2) &&
     this->is_free(pg3) && this->is_free(pg4) &&
     this->is_free(pg5) && this->is_free(pg6) &&
     this->is_free(pg6) && this->is_free(pg7))
     {
       free = true;
     }
  else
  {
    free = false;
  }

  return free;

}
