
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
#set(CMAKE_MACOSX_RPATH 1)
MESSAGE("${CMAKE_MODULE_PATH}")


################################################################################
SET(CMAKE_CXX_FLAGS "-std=c++11")

################################################################################
SET(_project "KalmanCpp")
SET(map_project "ISSPathPlanning")
PROJECT(${_project} CXX)
PROJECT(${map_project} CXX)

MESSAGE( "  ")
MESSAGE(STATUS "###############################################################")
MESSAGE( "  ")
MESSAGE(STATUS "  ${_project} : \n      ${_version}")
MESSAGE(STATUS "###############################################################")
MESSAGE( "  ")
################################################################################
################################################################################

# CXX flags

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -stdlib=libc++")

# DEFINITIONS
#INCLUDE(${CMAKE_SOURCE_DIR}/cmake/definitions.cmake)
################################################################################

# Include files:
################################################################################
INCLUDE_DIRECTORIES("include")
################################################################################

################################################### Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  #target_link_libraries(${_project} ${Boost_LIBRARIES})
endif()

################################################### VTK
set(VTK_INCLUDE_DIRS /usr/local/vtk-8.90/include)
set(VTK_DIR /usr/local/lib)
find_library(VTK_LIBRARIES HINT /usr/local/)
find_path(VTK_INCLUDE_DIRS /usr/local/vtk-8.90/include)
find_package(VTK REQUIRED )


set(VTK_USE_HYBRID ON)
set(VTK_USE_PATENTED ON)

if(VTK_FOUND)
  MESSAGE("ALL-MOD")

else()

  MESSAGE("MOD-BY-MOD")
  find_package(VTK COMPONENTS vtkFiltersCore
                              vtkFiltersSources
                              vtkInfovisLayout
                              vtkInteractionStyle
                              vtkRenderingCore
                              vtkRenderingFreeType
                              vtkRenderingOpenGL2
                              vtkViewsInfovis
                              vtkCommonCore
                              vtkCommonDataModel
                              vtkFiltersSources
                              vtkInteractionStyle
                              vtkRenderingContextOpenGL2
                              vtkRenderingFreeType
                              vtkRenderingGL2PSOpenGL2
                              vtkRenderingOpenGL2)
endif()

if (VTK_FOUND)
 unset(_vtk_targets)
 unset(_vtk_all_targets)
  include_directories(${VTK_INCLUDE_DIRS})
  include(${VTK_USE_FILE})

  MESSAGE("FOUND VTK @@@")
  MESSAGE(${VTK_INCLUDE_DIRS})
endif()
################################################### pcl
find_package(PCL 1.9 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})

################################################### 3dtlib
set(3DTlib_DIR /usr/local/Cellar/3DTlib/lib)
#FIND_PACKAGE(3DTlib REQUIRED HINT /usr/local/Cellar/3DTlib/lib )

FIND_PACKAGE(3DTlib REQUIRED)
include_directories(${3DTLIB_INCLUDE_DIR})

MESSAGE("FOUND 3DTLIB @@@")
MESSAGE(${3DTLIB_INCLUDE_DIRS})

################################################### gtest
include_directories(/Users/teobaiguera/Documents/Study/Kalman_Cpp/googletest/googletest/gtest/include)

SET(gtest_main_slib /Users/teobaiguera/Documents/Study/Kalman_Cpp/googletest/build/googlemock/gtest/libgtest_main.a)
SET(gtest_slib /Users/teobaiguera/Documents/Study/Kalman_Cpp/googletest/build/googlemock/gtest/libgtest.a)

####################################################  Program(s)
#file(GLOB ODE_SRCs "src/*.cpp" )
add_library(ODEs src/integration.cpp
                 src/collection.cpp
                 src/visualization.cpp
                 src/transformations.cpp
                 src/State.cpp
                 src/KalmanFilter.cpp
                 src/simulation.cpp
                 src/auxiliary.cpp
              )

add_library(MAPs  src/Map.cpp
                  src/BreadthFirstPathPlanner.cpp)

add_executable( ${_project}  main.cpp  )
add_executable( ${map_project}  map_generator.cpp  )
target_link_libraries(ODEs ${Boost_LIBRARIES}
                            ${VTK_LIBRARIES}
                            ${3DTLIB_LIBRARY}
                            ${PCL_LIBRARIES})

target_link_libraries (${_project} PUBLIC ODEs
                                          )

target_link_libraries (${map_project} PUBLIC MAPs
                                          ${Boost_LIBRARIES}
                                          ${3DTLIB_LIBRARY}
                                          ${PCL_LIBRARIES}
                                          ${gtest_slib}
                                          ${gtest_main_slib})

####################################################  Test(s)
add_subdirectory(test)
