cmake_minimum_required(VERSION VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")

project(Test)
enable_testing()

set(GTEST_SEARCH_DIR "../googletest/")
#set(GTEST_ROOT "/usr/local/Cellar/" CACHE PATH "Path to googletest")

find_package(PkgConfig REQUIRED)
#find_package(gtest)
#target_link_libraries(Test ${gtest_LIBRARIES})


add_executable(Test main_test.cpp ../include/Tester.h)

include_directories(/Users/teobaiguera/Documents/Study/Kalman_Cpp/googletest/googletest/gtest/include)

#!!!! IMPORTANT !!! Better to link project library to test instead of linking all 2 times

target_link_libraries(Test ${CMAKE_CURRENT_SOURCE_DIR}/../build/libODEs.a
                           ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/build/googlemock/gtest/libgtest.a
                           ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/build/googlemock/gtest/libgtest_main.a
                           )



add_test(NAME Test COMMAND Test)

add_custom_command(TARGET Test
                  COMMENT "Run tests"
                  POST_BUILD COMMAND ctest ARGS --output-on-failure
                  )
