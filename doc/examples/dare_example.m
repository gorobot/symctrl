clear
A = [1 -1 1; 0 1 1; 0 0 1];
B = [1 0; 1 0; 0 1];

Q = diag([10 1 0.1]);
R = diag([10 0.1]);

syms x1 x2 x3 u1 u2
sys = symss;
sys.states = [x1, x2, x3];
sys.inputs = [u1, u2];

sys.f = A*sys.states + B*sys.inputs;

% [X,L,G] = dare(A',H',Q,R)
[P, K] = dare(sys, Q, R)

%%
clear
A = [1 3; 1 2];
B = [1; -2];
Q = diag([0.2, 1]);
R = 0.5;

syms x1 x2 u1
sys = symss;
sys.states = [x1, x2];
sys.inputs = [u1];

sys.f = A*sys.states + B*sys.inputs;
sys.g = ones(2)*sys.states;

[P, K] = dare(sys, Q, R)

%%
clear
A = [0 2; 1 1];
B = [0; 1];
Q = [2.25, -1.5; -1.5, 1];
R = 2;

syms x1 x2 u1
sys = symss;
sys.states = [x1, x2];
sys.inputs = [u1];

sys.f = A*sys.states + B*sys.inputs;

[P, K] = dare(sys, Q, R)
