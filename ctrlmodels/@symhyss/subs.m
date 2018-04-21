function T = subs(sys, varargin)
%SUBS Replace symbolic variables in hybrid state space model.

switch nargin
    case 2
        new = varargin{1};
        
        T = sys;
        
        for k = 1:numel(sys.f)
            T.f{k} = subs(sys.f(k), new);
        end
        
        T.g = subs(sys.g, new);
        
    case 3
        old = varargin{1};
        new = varargin{2};
        
        T = sys;
        T.states = subs(sys.states, old, new);
        T.inputs = subs(sys.inputs, old, new);
        
        for k = 1:numel(sys.f)
            T.f{k} = subs(sys.f(k), old, new);
        end
        
        T.g = subs(sys.g, old, new);
        
    otherwise
        error('Incorrect arguments for subs.');
end

end

