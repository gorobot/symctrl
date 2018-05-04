%% Linear Response Example
% Example of simulating the linear response of a pendulum.

%% Load the System
sys = ctrldemo('pendulum4');

%% Linearize
% Linearize the system.
sys = linearize(sys|{m==1, g==9.8});

tspan = [0, 5];

%% Plot For Different Initial Conditions

initial(sys|{l==1, k==1}, tspan, {[1, 0], [pi, 0], [2*pi, 0]});

%% Plot For Different Lengths
figure
hold on
initial(sys|{l==1, k==1}, tspan, {[pi, 0]});
initial(sys|{l==2, k==1}, tspan, {[pi, 0]});
initial(sys|{l==3, k==1}, tspan, {[pi, 0]});
hold off

%% Plot For Different Damping Coefficients 
figure
hold on
initial(sys|{l==1, k==1}, tspan, {[pi, 0]});
initial(sys|{l==1, k==2}, tspan, {[pi, 0]});
initial(sys|{l==1, k==3}, tspan, {[pi, 0]});
hold off

%% Plot Time-Series Data
% We can also simulate a system to obtain an output function over all time
% given an arbitrary input. In our case, we can choose our input to be a
% step function.
syms s
u = -10*exp(-2*s)/s + 5*exp(-4*s)/s - 2.5*exp(-6*s)/s + exp(-8*s)/s;
y = lsim(sys|{l==1, k==1}, u, tspan, {[pi, 0]});

%%
% Plot time-series data for the output using a new time span. 
rg = 0:0.01:10;
ts = gettsdata(y{1}, rg);
plottsdata(ts, rg);
