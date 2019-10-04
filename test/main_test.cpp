#include <gtest/gtest.h>
#include "../include/Tester.h"
#include "../include/State.h"


#include "3DTlib/math/point.h"
#include "3DTlib/math/matrix/matrix.h"

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

TEST(FunctionFillingCube, CubeSizeTest){

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
       << s_t.get_p()[0] <<","
       << s_t.get_p()[1] <<","
       << s_t.get_p()[2] <<","
       << endl;

  cout << "velocity <==" <<endl
            << s_t.get_v()[0] <<","
            << s_t.get_v()[1] <<","
            << s_t.get_v()[2] <<","
            << endl;

  vector<double> v_tt = {p1[0],p1[1],p1[2],
                         v1[0],v1[1],v1[2]};
  State s_tt(v_tt);

  for (int i=0; i< 3; i++)
  {
    //First constructor
    EXPECT_EQ(s_t.p[i],p1[i]);
    EXPECT_EQ(s_t.v[i],v1[i]);

    //second constructor
    EXPECT_EQ(s_tt.p[i],p1[i]);
    EXPECT_EQ(s_tt.v[i],v1[i]);
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
    EXPECT_TRUE((s_sum.p[i] - (p1[i] + p2[i]) < 1e-7) || (s_sum.p[i] - (p1[i] + p2[i]) > -1e-7));
    EXPECT_TRUE((s_sum.v[i] - (v1[i] + v2[i]) < 1e-7) || (s_sum.p[i] - (v1[i] + v2[i]) > -1e-7));

    //Test diff
    EXPECT_TRUE((s_diff.p[i] - (p1[i] - p2[i]) < 1e-7) || (s_sum.p[i] - (p1[i] - p2[i]) > -1e-7));
    EXPECT_TRUE((s_diff.v[i] - (v1[i] - v2[i]) < 1e-7) || (s_sum.p[i] - (v1[i] - v2[i]) > -1e-7));


  }



}


GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
