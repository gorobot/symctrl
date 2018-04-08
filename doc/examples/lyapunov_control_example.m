sys = ctrldemo('pendulum4');
sys = sys|{g==9.8, k==1, l==1, m==1};
syms(sys.states)

%%
K = [1, 2];
u = -K*sys.states;

nlsim(sys, 0, [0 10], {[5, 5]})
nlsim(sys, u, [0 10], {[5, 5]})

%%
linsys = linearize(sys);
[~, V] = lyap(linsys);
u = lyapctrl(sys, V);

nlsim(sys, 0, [0 150], {[5, 5]})
nlsim(sys, u, [0 150], {[5, 5]})

% nlsim(sys, 0, [0 10], {[5, 5]})
% nlsim(sys, 1, [0 10], {[5, 5]})
% nlsim(sys, 2, [0 10], {[5, 5]})
