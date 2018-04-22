function sys = eom2symss(eqns, states)
%EQN2SYMSS Creates a state space model from symbolic equations of motion.
%   
%   sys = EOM2SYMSS(eqns, states)
%   
%   Creates a state space model according to the following rules:
%       1. Differentiate the states to opbtain the state equations.
%           .
%           x = d/dt(x)
%       2. For any derivatives of the states that are not also states,
%       solve the equations for the derivatives and replace them in the
%       state equations.

p = inputParser;
validateargs = @(arg) validateattributes(arg, {'sym'}, {'nonempty'});
addRequired(p, 'eqns', validateargs);
addRequired(p, 'states', validateargs);
parse(p, eqns, states);

sys = symss;
sys.states = states;

funs = diff(sys.states);
if has(funs, 'diff')
    % Get all unique higher derivatives.
    D = unique(getsymdiff(eqns));
    D = setdiff(D, sys.states);
    
    if ~isempty(D)
        % Create temporary variable names so that we can solve.
        nd = cell(size(D));
        nd(:) = {'DX'};
        td = sym(genvarname(nd, who));

        funs = subs(funs, D, td);
        teqns = subs(eqns, D, td);

        % Solve the equations for the temporary variables.
        S = solve(teqns, td);

        % Replace the temporary variables with solutions.
        if isstruct(S)
            funs = subs(funs, S);
        else
            funs = subs(funs, td, S);
        end
    end
end

sys.f = funs;

end

