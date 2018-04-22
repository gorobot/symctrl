%%
% Load the system. Van der Pol equation.
sys = ctrldemo('vanderpol2');

sys.f

%%
% Find the backward reachable set. 
x = {[1.5, 1.5]};

[R, S] = reach(sys, x, 'Points', 10, 'Tf', 1, 'Ts', 1E-3, ...
               'ComputationTime', Inf);

%%
% Plot the boundary of the regions.
b = boundary(R(:, 1), R(:, 2), 1);
plot(R(b, 1), R(b, 2));

hold on
b = convhull(S(:, 1), S(:, 2));
plot(S(b, 1), S(b, 2));
hold off

%%
% Simulate the system from initial conditions falling within the boundary.
polyin = polyshape(S(:, 1), S(:, 2));
[X, Y] = centroid(polyin);

nlsim2(sys, 0, [0 1], {[X, Y]});

