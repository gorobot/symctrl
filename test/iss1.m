clear, clc


syms x1 x2 u E r
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f(1) = -x1 + x1^2*x2;
sys.f(2) = -x1^3 - x2 + u;

u = 0;

V = lyap(sys);

GV = gradient(V)

X(r) = r/(1 - E);

ISS = GV.*sys.f

S = solve(ISS <= -X(norm(sys.states, 2)))
