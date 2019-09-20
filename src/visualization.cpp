#include "visualization.h"
void
display_trajectory(vector<state_type>& trajectory)
{

  /* Axes => already 'actor' */
  vtkSmartPointer<vtkAxesActor> axes =
                                    vtkSmartPointer<vtkAxesActor>::New();
  axes->SetXAxisLabelText("");
  axes->SetYAxisLabelText("");
  axes->SetZAxisLabelText("");
  axes->SetTotalLength(100,100,100);


  /* Master satellite */
  // STL reader
  vtkSmartPointer<vtkSTLReader> stl_reader;// = vtkSmartPointer<vtkSTLReader>::New();
  stl_reader = vtkSmartPointer<vtkSTLReader>::New();

  stl_reader->SetFileName(master_input_file_name);
  stl_reader->Update();

  vtkSmartPointer<vtkPolyDataMapper> master_mapper =
                                            vtkSmartPointer<vtkPolyDataMapper>::New();
  master_mapper->SetInputConnection(stl_reader->GetOutputPort());

  vtkSmartPointer<vtkActor> master_actor =
                                     vtkSmartPointer<vtkActor>::New();
  master_actor->SetMapper(master_mapper);
  master_actor->SetPosition(0,
                            0,
                            0);


  /* Slave satellite */
  // STL reader
  vtkSmartPointer<vtkSTLReader> stl_sat_reader;// = vtkSmartPointer<vtkSTLReader>::New();
  stl_sat_reader = vtkSmartPointer<vtkSTLReader>::New();

  stl_sat_reader->SetFileName(slave_input_file_name);
  stl_sat_reader->Update();

  vtkSmartPointer<vtkPolyDataMapper> sat_mapper =
                                                 vtkSmartPointer<vtkPolyDataMapper>::New();
  sat_mapper->SetInputConnection(stl_sat_reader->GetOutputPort());
  vtkSmartPointer<vtkActor> sat_actor =
                                     vtkSmartPointer<vtkActor>::New();


  sat_actor->SetMapper(sat_mapper);
  sat_actor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  //Initial position
  sat_actor->SetPosition(trajectory[0][0],
                         trajectory[0][1],
                         trajectory[0][2]);

  /* Camera */
  vtkSmartPointer<vtkCamera> camera =
                                      vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(0, 0, 100);
  //camera->SetFocalPoint(0, 0, 0);



  /* Renderer and Interactor*/
  //Declare interactor and renderer
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
                                              vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkRenderer> renderer =
                                vtkSmartPointer<vtkRenderer>::New();

  //Add camera
  renderer->SetActiveCamera(camera);

  // Add all actors
  renderer->AddActor(axes);
  renderer->AddActor(sat_actor);
  renderer->AddActor(master_actor);

  // Set Background
  renderer->SetBackground(0, 0, 0);


  /* Window */
  vtkSmartPointer <vtkRenderWindow> window =
                                     vtkSmartPointer<vtkRenderWindow>::New();

  window->SetMultiSamples(0);
  window->AddRenderer(renderer);
  iren->SetRenderWindow(window);

  /* Callback for animation */
  vtkSmartPointer<vtkTimerCallback2> cb =
                                      vtkSmartPointer<vtkTimerCallback2>::New();
  cb->actor = sat_actor;
  cb->trajectory = &trajectory;
  iren->AddObserver(vtkCommand::TimerEvent, cb);


  window-> Render();

  /* Callback animation */
  int timerId = iren->CreateRepeatingTimer((int)trajectory.size());
  //std::cout << "timerId: " << timerId << std::endl;

  /* Trajectory */
  for (auto p : trajectory)
  {
    //cout << p[0] << " , "<< p[1] << " , "<< p[2]<< endl;


    vtkSmartPointer<vtkSphereSource> pt =
                                          vtkSmartPointer<vtkSphereSource>::New();
    pt->SetRadius(.5);

    vtkSmartPointer<vtkPolyDataMapper> pt_mapper =
                                                   vtkSmartPointer<vtkPolyDataMapper>::New();
    pt_mapper->SetInputConnection(pt->GetOutputPort());

    vtkSmartPointer<vtkActor> pt_actor =
                                       vtkSmartPointer<vtkActor>::New();

    pt_actor->SetMapper(pt_mapper);
    pt_actor->SetPosition(p[0],p[1],p[2]);


    renderer->AddActor(pt_actor);



  }

  iren->Start();



}
