%% Controllability Example
% Example showing controllability analysis of symbolic state space models.

%% Controllability Analysis
% We can perform a controllability analysis of a system that is symbolic or
% even nonlinear using the Symbolic Controls Toolbox. Start by defining the
% state space model.
syms x1(t) x2(t) u

sys = symss;
sys.states = [x1 x2];
sys.inputs = u;

sys.f(1) = x1^2 + cos(x1)*x2;
sys.f(2) = u;

sys.A

%%
% The state space model has insufficient rank in its A matrix, but the
% controllability matrix of the system has sufficient rank to be
% controllable. We can observe the controllability matrix using `ctrb`.

Co = ctrb(sys)

%%
% We can see that the controllability matrix has rank 2, and is therefore
% controllable.

rank(Co)

%%
% We can also perform a simple check using the eigenvalue test for
% controllability using the function `iscontrollable`.

iscontrollable(sys)
