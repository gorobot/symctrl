function ob = obsv(obj)
%OBSV Computes the observability matrix of a state space model.
%
%   Ob = OBSV(sys) returns the observability matrix
%
%       [C; C*A; C*A^2; ...]
%
%   See also obsvs

%   References:
%   Antsaklis, Panos J., and Anthony N. Michel. A linear systems primer. Vol. 1.
%   Boston: Birkhauser, 2007.

n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);
p = calllib('matctrl', 'ml_statespace_g_size', obj.cobj_);

c = cell(1, n*p*n);
cptr = libpointer('stringPtrPtr', c);

calllib('matctrl', ...
        'ml_statespace_obsv', ...
        obj.cobj_, ...
        cptr);

% ob = cptr.Value;
ob = reshape(symctrl.se2mat(cptr.Value), n*p, n);

clear('cptr');

end
