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

Q = 1;
R = rho;

[K, P, L] = lqr(sys, Q, R);

%%
sys = symss([-3 2; 1 1], [0; 1], [1 -1], 0);

R = 3;
Q = 1;

[K, P, L] = lqr(sys, Q, R);

double(K)
double(P)
double(L)

