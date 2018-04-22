function y = impulse(sys, varargin)
%IMPULSE Compute the impulse response of a system.
%   y = IMPULSE(sys)

u = sym(1);

if nargout == 0
    lsim(sys, u, varargin{:});
else
    y = lsim(sys, u, varargin{:});
end

end

