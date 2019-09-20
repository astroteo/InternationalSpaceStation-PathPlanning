#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkSmartPointer.h"
#include <vtkAxesActor.h>
#include "AnimateActors.h"
#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkSTLReader.h>

#include <stdlib.h> // includes atoi
#include <iostream>

#include <string.h>

//#define master_input_file_name "../CADs/MRO_13.stl"
#define master_input_file_name "../CADs/Assembled_ISS.stl"
#define slave_input_file_name "../CADs/LRO_35_reduced.stl"

using namespace std;
typedef std::vector<double> state_type;



void display_trajectory(vector<state_type> &trajectory);
