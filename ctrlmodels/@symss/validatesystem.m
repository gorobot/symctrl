function validatesystem(sys, varargin)
%VALIDATESYSTEM Check validity of a system.
% 
%   VALIDATESYSTEM(sys, attributes) throws an error if system does not have
%   specified attributes.
%   
%   Attributes:
%       full - System must be fully defined.
%       hasinput - System inputs must be defined.
%       hasoutput - System output equations must be defined.
%       discrete - System must be discrete.
%       controllable - System must be controllable.
%       observable - System must be controllable.
% 
%       nstates - System must have N states.
%       ninputs - System must have N inputs.
%       nf - System must have N state equations.
%       ng - System must have N output equations.

p = inputParser;
validateChecks = @(C) validateattributes(C, {'cell'}, {'nonempty'});
addRequired(p, 'sys');
addOptional(p, 'attributes', cell.empty, validateChecks);
parse(p, sys, varargin{:});

attributes = p.Results.attributes;
va_ = @validateattributes;
mf_ = mfilename;
S = {'sym'};
N = {'numeric'};

for k = 1:numel(attributes)
    if ~ischar(attributes{k})
        continue;
    end
    
    switch attributes{k}
        % Attributes without arguments.
        case 'full'
            va_(sys.A, S, {'nonempty'}, mf_, 'state matrix');
            va_(sys.B, S, {'nonempty'}, mf_, 'input matrix');
            va_(sys.C, S, {'nonempty'}, mf_, 'output matrix');
            va_(sys.D, S, {'nonempty'}, mf_, 'feed-forward matrix');
        case 'hasinput'
            va_(sys.B, S, {'nonempty'}, mf_, 'input matrix');
        case 'hasoutput'
            va_(sys.C, S, {'nonempty'}, mf_, 'output matrix');
        case 'discrete'
            va_(sys.Ts, N, {'nonempty', 'positive'}, mf_, 'sampling time');
        case 'SISO'
            va_(sys.B, S, {'column'}, mf_, 'input matrix');
            va_(sys.C, S, {'row'}, mf_, 'output matrix');
        case 'controllable'
            if ~iscontrollable(sys)
                error('Expected system to be controllable.');
            end
        case 'observable'
            if ~isobservable(sys)
                error('Expected system to be observable.');
            end
        % Attributes with arguments.
        case 'nstates'
            nstates = getarg(attributes, k);
            va_(sys.states, S, {'numel', nstates}, mf_, 'states');
        case 'ninputs'
            ninputs = getarg(attributes, k);
            va_(sys.inputs, S, {'numel', ninputs}, mf_, 'inputs');
        case 'nf'
            nf = getarg(attributes, k);
            va_(sys.f, S, {'numel', nf}, mf_, 'state equations');
        case 'ng'
            ng = getarg(attributes, k);
            va_(sys.g, S, {'numel', ng}, mf_, 'output equations');
    end
end

    function arg = getarg(attr, k)
        try
            arg = attr{k + 1};
            if ischar(arg)
                error(['Invalid argument to ''', attr{k}, '''.']);
            elseif ~isnumeric(arg)
                error(['Argument to ', attr{k}, ' must be numeric.']);
            elseif isempty(arg)
                error(['Argument to ', attr{k}, ' must not be empty.']);
            end
        catch ME
            if strcmp(ME.identifier, 'MATLAB:badsubscript')
                error(['Insufficient arguments to ''', attr{k}, '''.']);
            else
                rethrow(ME);
            end
        end
    end

end

