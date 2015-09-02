function u = born(r)
%
% u = born(r)

kappa = 1.0;
epsilon_s = 80.0;
epsilon_m = 2.0;
Born_R = 0.5;
Born_a = 0.7;

Ceps = (1./epsilon_s - 1./epsilon_m);
Ckap = kappa/(epsilon_s*(1. + Born_a*kappa));

u = (abs(r)<Born_R)*(Ceps/Born_R - Ckap) + ...
    (abs(r)<Born_a).*(abs(r)>=Born_R).*(Ceps./abs(r)-Ckap) + ...
    (abs(r)>=Born_a).*(Ckap.*exp(-kappa*(abs(r)-Born_a))./(kappa*r)-1./(epsilon_m*abs(r)));
