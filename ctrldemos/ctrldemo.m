function D = ctrldemo(name, varargin)
%CTRLDEMO Loads a demo system from memory.
% 
%   Available demo systems:
%       - massspring    LTI, (Single mass)
%       - massspring2   LTI, (Double mass)
%       - pendulum      NLTI, (No friction)
%       - pendulum2     NLTI, (No constants)
%       - pendulum3     NLTI, (With constants)
%       - pendulum4     NLTI, (With constants, input)
%       - quadrotor     NLTI, (Quadrotor, euler angles)
%       - vanderpol     NLTI, (Van der Pol equation, forward time)
%       - vanderpol2    NLTI, (Van der Pol equation, reverse time)

p = inputParser;
validateName = @(arg) ...
    validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);
parse(p, name, varargin{:});

% Load the system.
S = load(name);
D = S.sys;

% Define constants in caller workspace.
for k = S.C{:}
    assignin('caller', char(k{:}), k{:});
end

end
