%% Nonlinear Response Example
% Example of a nonlinear system response.

%% Define the State Space Model
syms x1 x2
sys = symss;
sys.states = [x1 x2];
sys.f(1) = x2;
sys.f(2) = -10*sin(x1) - x2;

%% Plot the Response of One Variable
tspan = [0 10];
ic = {[1 0], [3 0], [pi 0]};

figure
nlsim(sys, tspan, ic, 'vars', {x1})

%% Plot the Response of Two Variables
figure
nlsim2(sys, tspan, ic, 'vars', {x1, x2});

%% Limit Cycles
sys.f(2) = -10*sin(x1);

figure
nlsim2(sys, tspan, ic, 'vars', {x1, x2},...
    'trajectory', 'on', 'solver', @ode15s);
