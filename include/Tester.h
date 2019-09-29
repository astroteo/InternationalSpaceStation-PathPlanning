#ifndef TESTER_EXISTING_H
#define TESTER_EXISTING_H
#include <gtest/gtest.h>
#include <vector>

using namespace std;

int
checkBoxDimensions(vector< vector< vector<int> > > int_grid,double length, double map_size)
{
  int f = 0;

  cout <<"x-span: "<< int_grid.size()
       <<"y-span: "<< int_grid[0].size()
       <<"z-span: "<< int_grid[0][0].size() << endl;

  for(int i=0; i<3; i++)
  {
    if(int_grid[i].size()  == (int) length/map_size )
    {
      f += 1;
    }
  }
  cout << "WTF ===>" << f << "<====" << endl;
  if (f<3)
   return 0;

  return 1;

}

GTEST_API_ int test_all(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}




#endif //TESTTESTER_EXISTING_H
