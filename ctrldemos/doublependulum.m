%% Double Pendulum
% Double pendulum equation.

% l1 - length of first arm
% l2 - length of second arm
syms l1 l2

theta1 = sym('x1');
dtheta1 = sym('x2');
theta2 = sym('x3');
dtheta2 = sym('x4');

sys = symss;
sys.states = [theta1 dtheta1 theta2 dtheta2];

sys.f(1) = l1*dtheta1*cos(theta1);
sys.f(2) = l1*dtheta1*sin(theta1);
