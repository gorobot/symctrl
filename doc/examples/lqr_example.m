%% LQR Example
% Example of computing the gain matrix, K, the solution to the ARE, P, and
% the eigenvalues of A-B*K, L.
syms x1 x2 u 
syms rho
assume(rho, 'real')
assumeAlso(rho, 'positive')
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f(1) = x2;
sys.f(2) = u;
sys.g(1) = x1;

Q = eye(2);
R = rho;

[K, P, L] = lqr(sys, Q, R);

%%
A = [-3, 2; 1, 1];
B = [0; 1];
C = [1, -1];

syms x1 x2 u
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f = A*sys.states + B*sys.inputs;
sys.g = C*sys.states;

R = 3;
Q = C.'*C;

[K, P, L] = lqr(sys, Q, R);

double(K)
double(P)
double(L)

