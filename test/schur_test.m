% A = [ 1 3 4
%       3 1 2
%       4 2 1 ]
A = [ -149    -50   -154
       537    180    546
       -27     -9    -25 ]

% A = [5 7; -2 -4]

[V, ~] = eig(sym(A))

[U1, S1] = schur(A);
[U2, S2] = schurs(sym(A));

% [U2, S2] = ordschurs(U2, S2);

% if ~isequal(U1, double(U2))
    disp(real([U1, double(U2)]))
% else
%     disp('equal')
% end
% if ~isequal(S1, double(S2))
    disp(real([S1, double(S2)]))
% else
%     disp('equal')
% end

% [V, D] = eig(sym(A));
% 
% disp(real([double(V), double(U2)]))
% disp(real([double(D), double(S2)]))
