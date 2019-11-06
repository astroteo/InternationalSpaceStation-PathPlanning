#include <gtest/gtest.h>
#include "../include/Tester.h"
#include "../include/State.h"
#include "../include/CostComparator.h"


#include "3DTlib/math/point.h"
#include "3DTlib/math/matrix/matrix.h"


#include <cmath>

TEST(StudyTestpp,FoolTests)
{


  int x=0;
  int y=0;

  int ppx = ++x;
  int ypp =y++;
  cout << "x = "<< x<< endl;
  cout << "++x = "<< ppx<< endl;

  cout << "y = "<< x<< endl;
  cout << "y++ = "<< ppx<< endl;

  ASSERT_EQ(1,ppx);
  ASSERT_EQ(0,ypp);
}

TEST(FunctionFillingCube, CubeSizeTest)
{

    double length= 6.;
    double map_size= 2.;
    vector< vector< vector<int> > > int_grid;
    std::vector<int> v = {1,2,3};
    std::vector<std::vector<int> > vv;
    vv.push_back(v);
    vv.push_back(v);
    vv.push_back(v);

    int_grid.push_back(vv);
    int_grid.push_back(vv);
    int_grid.push_back(vv);



    EXPECT_EQ(1, checkBoxDimensions(int_grid,length,map_size));

}


TEST(ClassStateTest, ClassStateTestConstructor)
{
  _3dtlib::Point p1(0,0,10);
  _3dtlib::Point v1(1,0,0);

  State s_t(p1,v1);
  cout << "position <==" <<endl
       << s_t.p()[0] <<","
       << s_t.p()[1] <<","
       << s_t.p()[2] <<","
       << endl;

  cout << "velocity <==" <<endl
            << s_t.v()[0] <<","
            << s_t.v()[1] <<","
            << s_t.v()[2] <<","
            << endl;

  vector<double> v_tt = {p1[0],p1[1],p1[2],
                         v1[0],v1[1],v1[2]};
  State s_tt(v_tt);

  for (int i=0; i< 3; i++)
  {
    //First constructor
    EXPECT_EQ(s_t.p()[i],p1[i]);
    EXPECT_EQ(s_t.v()[i],v1[i]);

    //second constructor
    EXPECT_EQ(s_tt.p()[i],p1[i]);
    EXPECT_EQ(s_tt.v()[i],v1[i]);
  }



}


TEST(ClassStateTest, ClassStateTestSum)
{
  _3dtlib::Point p1(0,0,10);
  _3dtlib::Point v1(1,0,0);

  State s1(p1,v1);

  _3dtlib::Point p2(0,0,10);
  _3dtlib::Point v2(1,0,0);

  State s2(p2,v2);

  State s_sum = s1 + s2;
  State s_diff= s1 - s2;

  for (int i=0; i< 3; i++)
  {

    //Test sum
    EXPECT_TRUE((s_sum.p()[i] - (p1[i] + p2[i]) < 1e-17) || (s_sum.p()[i] - (p1[i] + p2[i]) > -1e-17));
    EXPECT_TRUE((s_sum.v()[i] - (v1[i] + v2[i]) < 1e-17) || (s_sum.v()[i] - (v1[i] + v2[i]) > -1e-17));

    //Test diff
    EXPECT_TRUE((s_diff.p()[i] - (p1[i] - p2[i]) < 1e-17) || (s_sum.p()[i] - (p1[i] - p2[i]) > -1e-17));
    EXPECT_TRUE((s_diff.v()[i] - (v1[i] - v2[i]) < 1e-17) || (s_sum.v()[i] - (v1[i] - v2[i]) > -1e-17));


  }



}

TEST(MatrixStateMultiplyTest, ClassStateTestMatrixMultiply)
{

  _3dtlib::Matrixd A = {{1,0,0,0,0,0},
                        {0,1,0,0,0,0},
                        {0,0,1,0,0,0},
                        {0,0,0,1,0,0},
                        {0,0,0,0,1,0},
                        {0,0,0,0,0,1}};

  _3dtlib::Point pi(0,0,10);
  _3dtlib::Point vi(1,0,0);
  std::vector<double> s_ = {0.,0.,10.,1.,0.,0.};
  State s_i(s_);

  State s_new = A * s_i;

  cout << "x-old: " << s_i.p()[0]
       << " x-new: " << s_new.get_elements()[0]
       <<endl;

  cout << "y-old: " << s_i.p()[1]
       << " y-new: " << s_new.get_elements()[1]
       <<endl;

  cout << "z-old: " << s_i.p()[2]
       << " z-new: " << s_new.get_elements()[2]
       <<endl;

  for (unsigned int i=0; i<3 ; i++)
  {

    EXPECT_TRUE(abs(s_new.p()[i] - s_i.p()[i]) < 1e-17);
    EXPECT_TRUE(abs(s_new.v()[i] - s_i.v()[i]) < 1e-17);

  }

}


TEST(ClassCostComparator,ClassCostComparatorPropagationTest)
{

  CostComparator cc;
  State si(-20.735580,5.788168,4.799811,
            0.1      ,        0,    0.1);

  double dt = 1;
  State sf = cc.propagate_trajectory(si,dt);

  State sf_exact = State(-20.635619737170590,5.788055029931334,4.899807914279328,
                          0.099920504385605,-0.000225910193994,0.099993807277645);


  cout << "x-old: " << si.p()[0]
       << " x-new: " << sf.get_elements()[0]
       <<endl;

  cout << "y-old: " << si.p()[1]
       << " y-new: " << sf.get_elements()[1]
       <<endl;

  cout << "z-old: " << si.p()[2]
       << " z-new: " << sf.get_elements()[2]
       <<endl;


  for(unsigned int i=0; i<3; i++)
  {
    EXPECT_TRUE(abs(sf_exact.p()[i] - sf.p()[i]) < 1e-3);
    EXPECT_TRUE(abs(sf_exact.v()[i] - sf.v()[i]) < 1e-3);
  }



 }

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
