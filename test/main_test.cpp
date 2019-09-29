#include <gtest/gtest.h>
#include "../include/Tester.h"


TEST(FunctionFillingCube, FillingCubeTest){

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




GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
