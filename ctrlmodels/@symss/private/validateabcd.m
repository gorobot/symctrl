function validateabcd(A, B, C, D)
%VALIDATEABCD Validates whether matrix dimensions agree for a state space
%model.
%   
%   Checks whether A is nxn, B is nxm, C is pxn, and D is pxm.    

va_ = @validateattributes;
mf_ = mfilename;
SN = {'sym', 'numeric'};

% A should be square.
va_(A, SN, {'nonempty', 'square'}, mf_, 'state matrix');

n = size(A, 1);

% B should have n rows. C should have n columns.
va_(B, SN, {'size', [n, NaN]}, mf_, 'input matrix');
va_(C, SN, {'size', [NaN, n]}, mf_, 'output matrix');

[~, m] = size(B);
[p, ~] = size(C);

% D should be m x p.
va_(D, SN, {'size', [p, m]}, mf_, 'feed-forward matrix');

end
