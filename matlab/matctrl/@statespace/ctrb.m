function co = ctrb(obj)
%CTRB Computes the controllability matrix of a state space model.
%
%   Co = CTRB(sys) returns the controllability matrix
%
%       Co = [B, A*B, A^2*B, ...]
%
%   See also ctrbs

%   References:
%   Antsaklis, Panos J., and Anthony N. Michel. A linear systems primer. Vol. 1.
%   Boston: Birkhauser, 2007.

n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);
m = calllib('matctrl', 'ml_statespace_inputs_size', obj.cobj_);

c = cell(1, n*n*m);
cptr = libpointer('stringPtrPtr', c);

calllib('matctrl', ...
        'ml_statespace_ctrb', ...
        obj.cobj_, ...
        cptr);

% co = cptr.Value;
co = reshape(symctrl.se2mat(cptr.Value), n, n*m);

clear('cptr');

end
