% Create a nonlinear symbolic state-space model.
sys = statespace();

sys.states = {'x1', 'x2'};
sys.inputs = {'u'};
sys.f = {'x2', '-sin(x1) - x2 + u'};
sys.g = {'x1'};

% Get the nonlinear state matrices.
A = sys.A
B = sys.B
C = sys.C
D = sys.D

% Linearize the system around x = 0.
sys.linearize();

% View the linearized state matrices.
A = sys.A
B = sys.B
C = sys.C
D = sys.D

% Compute the controllability matrix for the linearized system.
Co = sys.ctrb()
