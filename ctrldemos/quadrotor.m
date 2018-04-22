%% Quadrotor
% Quadrotor dynamics, euler angles.

% References:
% Sabatino, F., Quadrotor Control: Modeling, Nonlinear Control Design, and
% Simulation, M.S. Thesis, Department of Electrical Engineering, KTH Royal
% Institute of Technology, Sweden, 2015.

% g - gravitational constant
% m - quadrotor mass
% l - distance from rotor to center of mass
% b - thrust factor
% d - drag factor
syms g m l b d

% The state varaibles describing the linear and angular position of the
% quadrotor in the earth frame are defined by [x, y, z, phi, theta, psi],
% while the state variables describing the linear and angular velocities of
% the quadrotor in the body frame are [u, v, w, p, q, r].

phi = sym('x1');
theta = sym('x2');
psi = sym('x3');

p = sym('x4');
q = sym('x5');
r = sym('x6');

u = sym('x7');
v = sym('x8');
w = sym('x9');

x = sym('x10');
y = sym('x11');
z = sym('x12');

% Body frame vectors.
vB = [u; v; w];
wB = [p; q; r];

c = @cos;
s = @sin;
t = @tan;

% Rotation transformation matrices.
Rx = [        1,       0,        0;
              0,  c(phi),  -s(phi);
              0,  s(phi),   c(phi)];

Ry = [ c(theta),       0, s(theta);
              0,       1,        0;
      -s(theta),       0, c(theta)];

Rz = [   c(psi), -s(psi),        0;
         s(psi),  c(psi),        0;
              0,       0,        1];

% Complete rotation transformation matrix.
R = Rz*Ry*Rx;

% Angular transformation matrix.
T = [         1, s(phi)*t(theta), c(phi)*t(theta);
              0,          c(phi),         -s(phi);
              0, s(phi)/c(theta), c(phi)/c(theta)];

% Inertia.
Jx = sym('Jx');
Jy = sym('Jy');
Jz = sym('Jz');

% Inputs.
ft = sym('u1');
tx = sym('u2');
ty = sym('u3');
tz = sym('u4');

% The disturbance inputs are the force applied to the quadrotor due to 
% wind [fwx fwy fwz] and the torques applied to the quadrotor due to wind
% [twx twy twz].
fwx = sym('fwx');
fwy = sym('fwy');
fwz = sym('fwz');

twx = sym('twx');
twy = sym('twy');
twz = sym('twz');

%% State-Space Model
sys = symss;
sys.states = [phi, theta, psi, p, q, r, u, v, w, x, y, z];
sys.inputs = [ft, tx, ty, tz];

sys.f(1:3) = T*wB;
sys.f(4) = r*q*(Jy - Jz)/Jx + (tx + twx)/Jx;
sys.f(5) = p*r*(Jz - Jx)/Jy + (ty + twy)/Jy;
sys.f(6) = p*q*(Jx - Jy)/Jz + (tz + twz)/Jz;
sys.f(7) = r*v - q*w - g*s(theta) + fwx/m;
sys.f(8) = p*w - r*u + g*s(phi)*c(theta) + fwy/m;
sys.f(9) = q*u - p*v + g*c(theta)*c(phi) + (fwz - ft)/m;
sys.f(10:12) = R*vB;

sys.g(1) = phi;
sys.g(2) = theta;
sys.g(3) = psi;
sys.g(4) = x;
sys.g(5) = y;
sys.g(6) = z;

%% Save System
savedemo('quadrotor', sys, {g, m, l, b, d, Jx, Jy, Jz});
