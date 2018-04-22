%% Reachability Analysis of an Inverted Pendulum
% Compute the controllability and observability matrices of an inverted
% pendulum and convert the system to controllable canonical form.

%% Compute the State Space Representation
% Compute the state space using the equations of motion for an inverted
% pendulum.
syms m l b g
syms theta(t) T y

f1 = m*l^2*diff(theta, t, t) + b*l*diff(theta, t) + m*g*l*sin(theta) == T;
g1 = y == theta;

states = {theta, diff(theta, t)};
inputs = {T};
outputs = {y};

sv = symsv({f1}, {g1}, ...
    'states', states, ...
    'inputs', inputs, ...
    'outputs', outputs);

sys = symss(sv);

sys.A

%% Compute the Controllability Matrix
% Once we have a state space representation, we can compute the
% controllability matrix using |ctrb|. 
Co = ctrb(sys)

%%
% Similarly, we can use |obsv| to compute the observability matrix for the
% symbolic state space.
Ob = obsv(sys)

%% Compute the Observable Canonical Form
% Given the state space representation of a system, we can compute the
% controllable or observable canonical forms using the command |canon|, and
% supplying either |'c'| or |'o'| as the canonical type.
sysC = canon(sys, 'type', 'o');

simplify(sysC.A)
simplify(sysC.B)
simplify(sysC.C)
