function K = place(sys, varargin)
%PLACE Compute closed-loop gain matrix K.
%   Detailed explanation goes here

p = inputParser;
[A, B, ~, ~] = getabcd(sys);
validatePoles = @(L) ...
    validateattributes(L, {'sym', 'numeric'}, {'row', 'numel', size(A, 1)});
addRequired(p, 'sys');
addOptional(p, 'P', sym.empty, validatePoles);
addOptional(p, 'r', sym.empty);
parse(p, sys, varargin{:});

K = sym('K', [1 size(A, 1)]);
K = subs(K, solve(A - B*K, K));

% Co = ctrbs(A, B);
% 
% if rank(Co) < length(A)
%     error('System is uncontrollable.');
% end
% 
% if any(strcmp('p', p.UsingDefaults))
%     
% end

end

