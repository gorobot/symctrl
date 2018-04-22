%% Thermostat
% The thermostat is a canonical hybrid switching model with 2 modes. Both
% modes are continuous "flow" modes, which represent when a heater
% controlled by the thermostat is either "on" or "off". 
% 
% Model:
% 
%   Mode 1                  Mode 2
%    _______________         ____________________
%   |               |       |                    |
%   | dx/dt = -a*x  | ----> | dx/dt = -a(x - 30) |
%   |               |       |                    |
%   | x >= 20       | <---- | x <= 22            |
%   |_______________|       |____________________|
% 
% Constants:
% a - temperature cooling coeficient, a < 1
syms a

syms x
sys = symhyss;
sys.states = x;

sys.f(1, 1) = -a*x;
sys.guard(1, 2) = x >= 20;

sys.f(2, 1) = -a*(x - 30);
sys.guard(2, 1) = x <= 22;

savedemo('thermostat', sys, {a});
