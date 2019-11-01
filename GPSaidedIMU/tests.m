%% Nav eq test

x = [1.    ,1.    ,0.    ,0.1   ,0.1   ,0.    ,0.    ,0.    ,0.7071, 0.7071]';
u = [1,0, 0,1,2,0]';
dt = 0.01;
x_t = Nav_eq(x,u,dt);

%% State-Space test
[F_t,G_t]=ss_model(x,u,dt);

disp('F<=')
disp(F_t)

disp('G<=')
disp(G_t)



%% Kf gain test




%% Kf update test