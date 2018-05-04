function sys = subs(sys, varargin)
%SUBS Replace symbolic variables in hybrid state space model.

sys = copy(sys);

for k = 1:sys.nmodes
    sys.f_{k} = subs(sys.f_{k}, varargin{:});
end

sys.g = subs(sys.g, varargin{:});

end
