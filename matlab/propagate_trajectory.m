function [Rho_Ni_f] = propagate_trajectory(Rho_Ni_i,tau)
W = 0.00113;

Ct=cos(W*tau);
St=sin(W*tau);


PHI=[4-3*Ct       0      0       St/W          2/W*(1-Ct)          0;
    6*(St-W*tau)  1      0    -2/W*(1-Ct)    1/W*(4*St-3*W*tau)    0;
        0         0      Ct       0                0           1/W*St;
     3*W*St       0      0        Ct             2*St              0;
   -6*W*(1-Ct)    0      0      -2*St           4*Ct-3             0;
        0         0    -W*St      0                0              Ct ];
    
Rho_Ni_f = PHI * Rho_Ni_i;


return



tau = 1
Rho_0 = [-20.735580;5.788168;4.799811] 
Ni_0 = [0.1; 0; 0.1]

Rho_Ni_0 = [Rho_0; Ni_0]

Rho_Ni_f = propagate_trajectory(Rho_Ni_0,tau)






    