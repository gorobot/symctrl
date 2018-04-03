function R = roa(sys, varargin)
%ROA Calculate region of attraction for a nonlinear system.
%   
%   R = ROA(sys) calculates the region of attraction for a state space
%   system using the Lyapunov function derived from the Lyapunov equation.
% 
%   R = ROA(sys, V) calculates the region of attraction for a state space
%   model using a given Lyapunov equation.
%   
%   To calculate the region of attraction, the system performs the
%   following steps:
%   1. Calculate the derivative of the Lyapunov function.
%   2. Obtain solutions for:
%       .
%       V = 0
%   3. Solve for the equation:
%       V(z), where 'z' are the solutions to the previous equation.
% 
%   The result R is the greatest solution to the equation V(z) = R.
% 
%   ROA(____) plots the region of attraction for a state space model
%   using a given Lyapunov equation.
% 
%   See also symss/elroa

p = inputParser;
addRequired(p, 'sys');
addOptional(p, 'V', sym.empty);
addParameter(p, 'Trajectory', false);
parse(p, sys, varargin{:});

if any(strcmp('V', p.UsingDefaults))
    linsys = linearize(sys);
    V = lyap(linsys);
else
    V = p.Results.V;
end

dV = lyapdiff(sys, V);
    
[tx, tu, ~, ~] = varsub(sys);
tv = subs(V, [sys.states; sys.inputs], [tx; tu]);
dV = subs(dV, [sys.states; sys.inputs], [tx; tu]);

% tv = subs(V, [sys.states; sys.inputs], [tx; tu]);

% if isequal(dV, 0)
%     error('Unable to calculate derivative of V.');
% end

% DV = subs(DV, Dx, sys.f);

% V = formula(subs(V, sys.states, tx));
% DV = formula(subs(DV, sys.states, tx));

try
    sols = solve(dV, tx);
    sols = struct2cell(sols);
    if ~isempty(sols)
        Vfun = symfun(tv, tx);
        R = double(max(Vfun(sols{:})));
    end
    
catch ME
    if strcmp(ME.identifier, 'something')
        % do something
    else
        rethrow(ME)
    end
end

if nargout == 0 && numel(sys.states) <= 2
    % Plot ROA curve.
    fi = fimplicit(Vfun == R);

    rgx = fi.XRange*1.5;
    rgy = fi.YRange*1.5;
    fi.XRange = rgx;
    fi.YRange = rgy;
    fi.XRangeMode = 'auto';
    fi.YRangeMode = 'auto';

    [X, Y] = meshgrid(linspace(rgx(1), rgx(2), 20), ...
                      linspace(rgy(1), rgy(2), 20));

    ax = gca;
    axcs = ax.NextPlot;

    % Plot VDot.
%     ax.NextPlot = 'add';
%     fimplicit(dV)
%     Z = subs(DV, tx, {X; Y});
%     contour(X, Y, Z, 0:5);

    % Plot function trajectories.
    if p.Results.Trajectory
        ax.NextPlot = 'add';
        F1 = subs(sys.f(1), sys.states, {X; Y});
        F2 = subs(sys.f(2), sys.states, {X; Y});
        q = quiver(ax, X, Y, F1, F2);
        q.AutoScale = 'on';
        q.AlignVertexCenters = 'on';
    end

    ax.NextPlot = axcs;
end

end
