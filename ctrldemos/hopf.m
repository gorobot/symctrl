%% Supercritical Hopf Bifurcation
% Example of the supercritical Hopf bifurcation. The limit cycle has a
% value of sqrt(mu) when mu > 0, and no limit cycle when mu < 0. 

syms x1 x2 u mu
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;

sys.f(1) = x1*(mu - x1^2 - x2^2) - x2;
sys.f(2) = x2*(mu - x1^2 - x2^2) + x1;

% nlsim2(sys, 0, [0 10], {[2, 2], [-2, 2], [-2, -2], [2, -2], ...
%                         [1E-2, 0], [-1E-2, 0], [0, -1E-2], [0, 1E-2]});

savedemo('hopf', sys, {mu});
