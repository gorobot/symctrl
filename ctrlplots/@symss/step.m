function y = step(sys, varargin)
%STEP Compute the step response of a system.
%   y = STEP(sys)

syms s
u = 1/s;

if nargout == 0
    lsim(sys, u, varargin{:});
else
    y = lsim(sys, u, varargin{:});
end

end

