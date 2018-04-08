function T = kalmanform(sys)
%KALMANFORM Kalman decomposition.
%   
%   T = KALMANFORM(sys) converts a state space model to its Kalman
%   decomposition.

%   References:
%   R. E. Kalman, "On the Computation of the Reachable/Observable 
%   Canonical Form," SIAM J. Control and Optimization, Vol. 20, No. 2, 
%   pp. 258-260, 1982
% 
%   Dahleh, Mohammed, Munther A. Dahleh, and George Verghese. "Lectures on
%   dynamic systems and control." A+ A 4.100 (2004): 1-100.
% 
%   http://ece.iit.edu/~gaw/ece531/ECE531_18S_kalman.pdf
%   https://ece.gmu.edu/~gbeale/ece_521/xmpl-521-kalman-min-real-01.pdf

[A, B, C, ~] = getabcd(sys);

% Find the controllability and observability matrices. 
Co = ctrbs(A, B);
Ob = obsvs(A, C);

% Compute an orthonormal transformation matrix.
P = orth([Co, null(Ob), eye(size(A))], 'real');

% Compute the Kalman decomposition of the system.
T = symss2symss(sys, P.');

end

