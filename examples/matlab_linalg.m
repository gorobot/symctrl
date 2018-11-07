% Matlab setup.
syms a b c
A = [3, 4, 5;
     2, 3, 4;
     a, b, c];

H = [-149, -50, -154;
      537, 180,  546;
      -27,  -9,  -25];

% Start the timer.
tic

% Upper-Hessenberg Form
B = symctrl.hess(A);
toc

% Schur Decomposition
[U, T] = symctrl.schur(H);
toc
