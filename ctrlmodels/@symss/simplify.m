function T = simplify(sys, varargin)
%SIMPLIFY Simplify a state space model.
%
%   sys = SIMPLIFY(sys, ...)
%   simplifies the state and output equations for a state space model.
%   Extra parameters are passed to the internal sym/simplify calls.
%   
%   Used to apply assumptions defined in the workspace to a state space
%   model. Does not apply assumptions that affect state variables or input
%   variables.
% 
%   See also sym/simplify

p = inputParser;
addRequired(p, 'sys');
parse(p, sys);

T = sys;
T.f = simplify(sys.f, varargin{:});
T.g = simplify(sys.g, varargin{:});

end
