function T = c2d(sys, varargin)
%C2D Convert continuous state-space model to discrete model.
%   
%   T = C2D(sys, Ts) converts a continuous state-space model to a discrete model
%   with sampling time Ts.

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'continuous'}));
addOptional(p, 'Ts', 1, ...
    @(arg) validateattributes(arg, {'numeric'}, {'positive'}));
addParameter(p, 'Method', 'zoh');
parse(p, sys, varargin{:});

Ts = p.Results.Ts;
method = p.Results.Method;

[A, B] = sys.getabcd();
T = symss;

switch method
    case 'zoh'
        % Zero-Order Hold
        % Ad = e^AT
        % Bd = A^-1(Ad - I)B
        Ad = subs(expm(sys), sym('t'), Ts);
        Bd = A\(Ad - eye(size(A)))*B;
        
    case 'approx'
        % Approximate Discretization
        % Ad = (I + AT)
        % Bd = TB
        Ad = eye(size(A)) + A*Ts;
        Bd = Ts*B;
        
    otherwise
        error(['Method ''', method, ''' is not supported.']);
end

T.Ts = Ts;
T.states = sys.states;
T.inputs = sys.inputs;
T.f = Ad*T.states + Bd*T.inputs;
T.g = sys.g;

end

