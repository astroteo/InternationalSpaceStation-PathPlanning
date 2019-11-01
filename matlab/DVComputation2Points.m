
clear all
close all
%% Params 
%orbit
Mu=(3.9856e+14);
r_Earth=6380*10^3;

h_orb=400*10^3;
i_orb=51.65*pi/180;
%i_orb=0;
om_orb=0;
OM_orb=0;
theta0_orb=0;
a_orb=r_Earth+h_orb;
e_orb=0;


T_orb=2*pi*sqrt((r_Earth+h_orb)^3/Mu)

omega=sqrt(Mu/((r_Earth+h_orb)^3));
w=omega;
setGlobalW(w)

%% Start and end point

x_obs=200+3
y_obs=-300-3
z_obs=0

Rho_0_2d=[x_obs-0.5,y_obs +0.5];
Rho_0_3d=[Rho_0_2d(1);Rho_0_2d(2);0];


X_obs_3d=[x_obs;y_obs;z_obs];

%% default computation [ X0,Xf, @tau] -> [V0,]

tau=1/4*T_orb;

Ct=cos(w*tau);
St=sin(w*tau);


det=(4*St)/(w^3) -(8*Ct*St)/(w^3) +(4*Ct^2*St)/(w^3)+(4*St^3)/(w^3) -(3*St^2*tau)/(w^2);

N_tau_inv=1/det*[(4*St^2)/(w^2)-(3*St*tau)/w,     -((2*St)/(w^2))+(2*Ct*St)/(w^2),                        0;
                 (2*St)/(w^2)-(2*Ct*St)/(w^2),              St^2/(w^2),                                   0;
                           0,                                  0,              4/(w^2)-(8*Ct)/(w^2)+(4*Ct^2)/(w^2)+(4*St^2)/(w^2)-(3*St*tau)/w];
                   
M_tau=[-3*Ct+4,        0,   0;
        6*St-6*w*tau,  1,   0;                   
               0    ,  0,  Ct];


Ni_0_3d=N_tau_inv*(X_obs_3d-M_tau*Rho_0_3d);




%% plot to see if exists minima

tau_span = linspace(1/500*tau, 3.9*tau,20000);
DV_span = zeros(size(tau_span));
i =1
DV_min = inf;

for t = tau_span
    tau = tau_span(i);

    Ct=cos(w*tau);
    St=sin(w*tau);


    det=(4*St)/(w^3) -(8*Ct*St)/(w^3) +(4*Ct^2*St)/(w^3)+(4*St^3)/(w^3) -(3*St^2*tau)/(w^2);

    N_tau_inv=1/det*[(4*St^2)/(w^2)-(3*St*tau)/w,     -((2*St)/(w^2))+(2*Ct*St)/(w^2),                        0;
                     (2*St)/(w^2)-(2*Ct*St)/(w^2),              St^2/(w^2),                                   0;
                               0,                                  0,              4/(w^2)-(8*Ct)/(w^2)+(4*Ct^2)/(w^2)+(4*St^2)/(w^2)-(3*St*tau)/w];

    M_tau=[-3*Ct+4,        0,   0;
            6*St-6*w*tau,  1,   0;                   
                   0    ,  0,  Ct];


    Ni_0_3d = N_tau_inv*(X_obs_3d-M_tau*Rho_0_3d);
    
    
    
    DV_span(i) = norm(Ni_0_3d);
    i = i+1;
    
    if norm(Ni_0_3d) < DV_min
        min_Ni_0_3d = Ni_0_3d;
        tau_min = tau;
        DV_min = norm(Ni_0_3d);
    end
   
    
end


plot(tau_span,DV_span)
grid on



t_end=tau;
X_0_3d=[Rho_0_3d;min_Ni_0_3d];

options = odeset('RelTol',1e-13,'AbsTol', 1e-12);
[t_CW_FD,x_CW_FD]= ode113('Chol_Wilt_Hill',tau_min,X_0_3d,options);%<--[]

[CW_FD,~]=size(t_CW_FD);
zebra_FD=zeros(CW_FD,1);

figure()
hold on
plot3(x_CW_FD(:,1),x_CW_FD(:,2),zebra_FD,'--b',x_CW_FD(1,1),x_CW_FD(1,2),zebra_FD,'og',x_CW_FD(end,1),x_CW_FD(end,2),zebra_FD,'or',x_obs,y_obs,0,'*b')
grid on 





