function T = subs(sys, varargin)
%SUBS Replace symbolic variables in state space model.
%   
%   sys = SUBS(sys, ...) replaces symbolic variables, state variables, or
%   input variables in the state equations of a state space model.
%   
%   Use this method instead of symss/simplify to replace state variables
%   and input variables in the state equations.
% 
%   sys = SUBS(sys, new) replaces symbolic variables, state variables, or
%   input variables in the state space model.
%   
%   sys = SUBS(sys, old, new) replaces symbolic variables, state variables,
%   input variables, or symbolic functions in the state equations.
% 
%   See also sym/subs

switch nargin
    case 1
        T = simplify(sys);
        
    case 2
        old = reshape([sys.states; sys.inputs], [], 1);
        new = reshape(varargin{:}, [], 1);

        T = sys;
        T.states = subs(sys.states, old, new);
        T.inputs = subs(sys.inputs, old, new);
        T.f = subs(sys.f, old, new);
        T.g = subs(sys.g, old, new);
    
    otherwise
        T = sys;
        T.f = subs(sys.f, varargin{:});
        T.g = subs(sys.g, varargin{:});
end

end
