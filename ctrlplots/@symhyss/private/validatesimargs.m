function validatesimargs(p, sys, varargin)
%VALIDATESIMARGS Validates simulation inputs.

va_ = @validateattributes;

validateattributes(sys.states, {'sym'}, {'nonempty'});
for k = 1:sys.nmodes
    validateattributes(sys.f{k}, {'sym'}, {'nonempty'});
end

nX = numel(sys.states);

p.StructExpand = false;

addRequired(p, 'sys');

% Validate sim inputs.
if ~isempty(sys.inputs)
    nU = numel(sys.inputs);
    addOptional(p, 'u', ...
        zeros([nU, 1]), ...
        @(arg) va_(arg, {'sym', 'numeric', 'function_handle'}, ...
                   {'numel', nU}));
else
    addOptional(p, 'u', ...
        0, ...
        @(arg) va_(arg, {'sym', 'numeric'}, {'nonempty'}));
end

% Validate time span.
if isempty(sys.Ts)
    defaulttspan = [0 5];
else
    defaulttspan = 0:sys.Ts:sys.Ts*100;
end

addOptional(p, 'tspan', ...
    defaulttspan, ...
    @(arg) va_(arg, {'numeric'}, {'row', 'nonnegative', 'increasing'}));

% Validate initial conditions.
addOptional(p, 'x0', ...
    {zeros([nX, 1])}, ...
    @(arg) va_(arg, {'sym', 'numeric', 'cell'}, {'nonempty'}));

% Validate ode options.
addOptional(p, 'options', ...
    struct([])), ...
    @(arg) va_(arg, {'struct'}, {'nonempty'});

% Validate return variables.
addParameter(p, 'Vars', ...
    cell.empty, ...
    @(arg) validateattributes(arg, {'sym', 'cell'}, {'row', 'nonempty'}));

% Validate ODE solver.
addParameter(p, 'Solver', ...
    @ode45, ...
    @(arg) validateattributes(arg, {'function_handle'}, {'nonempty'}));

% Parse inputs.
parse(p, sys, varargin{:});

% Check initial conditions.
x0 = p.Results.x0;
if ~iscell(x0)
    x0 = {x0};
end

for k = 1:numel(x0)
    va_(x0{k}, {'sym', 'numeric'}, {'vector', 'numel', nX});
end

% Check variables.
if ~any(strcmp(p.UsingDefaults, 'Vars'))
    if ~any(ismember(p.Results.Vars, sys.states))
        error('Variables in ''Vars'' must be a state variable.');
    end
end

end
