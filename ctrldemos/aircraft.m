%% Aircraft (6-DOF)
% 6-DOF Aircraft Demo System
% 
% Constants
% Jx - Inertia for x.
% Jy - Inertia for y.
% Jz - Inertia for z.
syms Jx Jy Jz Jxz Mx My Mz T g m

phi = sym('x1');
theta = sym('x2');
psi = sym('x3');

x = sym('x4');
y = sym('x5');
z = sym('x6');

p = sym('x7');
q = sym('x8');
r = sym('x9');

u = sym('x10');
v = sym('x11');
w = sym('x12');

fx = sym('fx');
fy = sym('fy');
fz = sym('fz');

c = @cos;
s = @sin;
t = @tan;

% State-space model.
sys = symss;
sys.states = [phi, theta, psi, x, y, x, p, q, r, u, v, w];
sys.inputs = u;

sys.f(1) = p + r*c(phi)*t(theta) + q*s(phi)*tan(theta);
sys.f(2) = q*c(phi) - r*s(phi);
sys.f(3) = (r*c(phi) + q*s(phi))/c(theta);
sys.f(4) = u*c(theta)*c(psi) + c(phi)*(w*cos(psi)*s(theta) - v*sin(psi)) + s(phi)*(v*c(psi)*s(theta) + w*s(psi));
sys.f(5) = -w*c(psi)*s(phi) + (u*c(theta) + v*s(theta)*s(phi))*s(psi) + c(phi)*(v*c(psi) + w*s(theta)*s(psi));
sys.f(6) = -u*s(theta) + c(theta)*(w*c(phi) + v*s(phi));
sys.f(7) = -(Jz*(p*q*Jxz + q*r*Jy - q*r*Jz + Mx) + Jxz*(p*q*Jx - q*r*Jxz - p*q*Jy + Mz))/(Jxz^2 - Jx*Jz);
sys.f(8) = (-p*r*Jx + (-p^2 + r^2)*Jxz + p*r*Jz + My)/Jy;
sys.f(9) = (p*q*Jx^2 + Jxz*(p*q*Jxz + q*r*Jy - q*r*Jz + Mx) + Jx*(-q*r*Jxz - p*q*Jy + Mz))/(-Jxz^2 + Jx*Jz);
sys.f(10) = r*v - q*w + (T + fx - g*m*s(theta))/m;
sys.f(11) = -r*u + p*w + fy/m + g*c(theta)*s(phi);
sys.f(12) = q*u - p*v + fz/m + g*c(theta)*c(phi);

