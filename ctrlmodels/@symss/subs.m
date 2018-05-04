function sys = subs(sys, varargin)
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
%   See also symss/simplify, sym/subs

sys = copy(sys);
sys.f = subs(sys.f, varargin{:});
sys.g = subs(sys.g, varargin{:});

end
