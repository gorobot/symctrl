clear, clc

syms s b m k y t
G = symtf([4.2,0.25,-0.004], [1,9.6,17]);
% pole(G)
% zero(G);

% G = symtf([1.65 -0.331 -576 90.6 19080], [1 0.996 463 97.8 12131 8.11 0]);
% sys = symtf2symss(G);

sys = symtf2symss(G);
% [A, B, C, D] = sys.getmatrices();
% A = double(A);
% B = double(B);
% C = double(C);
% D = double(D);
% s = ss(A, B, C, D);
% 
% step(s)

u = exp(-1*s)/s - exp(-2*s)/s + exp(-3*s)/s - exp(-4*s)/s;

hold on
initial(sys)
impulse(sys)
step(sys);
lsim(sys, u);
hold off

% Csys = canon(sys, 'c');

% pole(G)

% ishurwitz(G)

% islipschitz(sqrt(abs(y)), y, [-1 5])
% islipschitz(sin(1/y), y)
% islipschitz(abs(y), y)
% islipschitz(G.tf, s)
