%% Mass Spring Response
% An example of obtaining the response of a double mass-spring system.

%% Define Symbolic Variables
% Define the state variables, input variables, and any constants.
syms M1 B B1 K K1 M2 B2 K2 t positive
syms u1(t) u2(t)
syms y1(t) y2(t)

%% Define the State Space Model
% The system is defined by the equations of motion:
% 
% $$M_1\ddot{y_1} + (B + B_1)\dot{y_1} + (K + K_1)y_1 - B\dot{y_2} - Ky_2 = u_1$$
% 
% $$M_2\ddot{y_2} + (B + B_2)\dot{y_2} + (K + K_2)y_2 - B_1\dot{y_1} - Ky_1 = u_2$$

f1 = M1*diff(y1, t, t) + (B + B1)*diff(y1, t) + (K + K1)*y1 - B*diff(y2, t) - K*y2 == u1;
f2 = M2*diff(y2, t, t) + (B + B2)*diff(y2, t) + (K + K2)*y2 - B1*diff(y1, t) - K*y1 == -u2;

%%
% Convert the equations of motion to state space form. The state variables
% are defined as $y_1$, $\dot{y_1}$, $y_2$, $\dot{y_2}$.
sys = eom2symss([f1, f2], [y1, diff(y1, t), y2, diff(y2, t)]);

%%
% Specify the inputs as $u_1$ and $u_2$.
sys.inputs = [u1 u2];

%%
% Define the output equations.
sys.g(1) = y1;
sys.g(2) = y2;

%% Specify Initial Conditions
% Specify constant values and initial conditions. 
cons = {M1==0.1, B==1, B1==1, K==1, K1==1, M2==2, B2==1, K2==1};
ic = [1 0 0 0];

%%
% Obtain the symbolic system response.
y = step(sys|cons, ic);

%%
% Define the time interval to plot over and get the time-series data for
% the system response.
T = 0:0.1:10;
ts = gettsdata(y, T);

%%
% Plot the system response for the time series data obtained.
plottsdata(ts, T);
