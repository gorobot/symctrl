function T = d2c(sys, varargin)
%D2C Convert discrete state-space model to continuous model.
%   
%   T = C2D(sys) converts a discrete state-space model to a continuous model.

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'discrete'}));
addOptional(p, 'Ts', 1, ...
    @(arg) validateattributes(arg, {'numeric'}, {'positive'}));
addParameter(p, 'Method', 'zoh');
parse(p, sys, varargin{:});

method = p.Results.Method;

Ts = sys.Ts;
[Ad, Bd] = sys.getabcd();
T = symss;

switch method
    case 'zoh'
        % Zero-Order Hold
        % Ad = e^AT
        % Bd = A^-1(Ad - I)B
        syms s t
        A = laplace(Ad, t, s);
        B = A\(Ad - eye(size(A)))*Bd;
        
    case 'approx'
        % Approximate Discretization
        % Ad = I + AT
        % Bd = TB
        A = (Ad - eye(size(Ad)))/Ts;
        B = Bd/Ts;
        
    otherwise
        error(['Method ''', method, ''' is not supported.']);
end

T.Ts = Ts;
T.states = sys.states;
T.inputs = sys.inputs;
T.f = A*T.states + B*T.inputs;
T.g = sys.g;

end

