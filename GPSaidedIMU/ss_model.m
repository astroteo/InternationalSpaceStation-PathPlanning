function [F,G]=ss_model(x,u,Ts)

% Convert quaternion to DCM
disp('<= q')
disp(x(7:10))
Rb2t=q2dcm(x(7:10));
disp('<= Rb2t')
disp(Rb2t)

% Transform measured force to force in
% the tangent plane coordinate system.
f_t=Rb2t*u(1:3);
St=[0 -f_t(3) f_t(2); f_t(3) 0 -f_t(1); -f_t(2) f_t(1) 0];
disp('<= Sn')
disp(St)

% Only the standard errors included
O=zeros(3);
I=eye(3);
Fc=[O I O O O;
    O O St Rb2t O;
    O O O O -Rb2t;
    O O O O O;
    O O O O O];

% Approximation of the discret
% time state transition matrix
F=eye(15)+Ts*Fc;

% Noise gain matrix
G=Ts*[O O O O; Rb2t O O O; O -Rb2t O O; O O I O; O O O I];
end