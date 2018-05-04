%% MDP Grid World Maze Example
% Example showing an MDP solving a maze in the canonical grid world example
% using a nonholonomic robot.

%% Define the Continuous Dynamics
% For this example, we use a nonholonomic robot.

sys = ctrldemo('nonholonomic');
sys = subs(sys, d, 1);

%% Create a Markov Decision Process
% Create an MDP for the system.

m = mdp;

%% Discretize the State Space
% Discretize the state space to create a 10x10 grid, with 4 possible directions
% the robot can be facing.

[X, in, Xf] = dspace(m, sys, {0:10, 0:10, -pi/4:pi/2:7*pi/4});

m.X = X;

%% Create the Inputs
% We define three possible inputs for the robot: move forward, turn left, and
% turn right.

m.U{1} = [1, 1];

m.U{2} = [-pi/4, pi/4];

m.U{3} = [pi/4, -pi/4];

%% Propagate the Probability Space
% For this example, we assume that if the robot takes an action, that it has a
% 100% chance of reaching its target state. We define the probability moving
% forward and turning. 
% 
% For the turns, we do not allow the robot to rotate 360 degrees. This is
% because if the robot turns left while its angle is 270 degrees, it will reach
% 360 degrees and is no longer in the state space we have defined.

pattern = zeros(3, 3, 3);

pattern(:, :, 2) = [0, 0, 0; 0, NaN, 0; 0, 1, 0];
propp(m, {1:9, NaN, 1}, 1, pattern);

pattern(:, :, 2) = [0, 0, 0; 0, NaN, 1; 0, 0, 0];
propp(m, {NaN, 1:9, 2}, 1, pattern);

pattern(:, :, 2) = [0, 1, 0; 0, NaN, 0; 0, 0, 0];
propp(m, {2:10, NaN, 3}, 1, pattern);

pattern(:, :, 2) = [0, 0, 0; 1, NaN, 0; 0, 0, 0];
propp(m, {NaN, 2:10, 4}, 1, pattern);

pattern = zeros(1, 1, 4);

pattern(:, :, :) = [NaN; 1; 0; 0];
propp(m, [NaN, NaN, 1], 2, pattern);
propp(m, [NaN, NaN, 2], 2, pattern);
propp(m, [NaN, NaN, 3], 2, pattern);

pattern(:, :, :) = [0; 0; 1; NaN];
propp(m, [NaN, NaN, 2], 3, pattern);
propp(m, [NaN, NaN, 3], 3, pattern);
propp(m, [NaN, NaN, 4], 3, pattern);

%% Propagate the Reward Space
% For this example, we create a maze of penalties that the robot must navigate.
% We create the maze in 2-D for x/y and propagate it through all possible
% angles.
% 
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     1 |     |     |     |     |     |     |     |     | -100| 100 |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     2 |     | -100| -100| -100| -100| -100| -100|     | -100|     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     3 |     | -100|     |     |     |     | -100|     | -100|     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     4 |     | -100| -100|     | -100| -100| -100|     | -100|     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     5 |     |     |     |     |     | -100|     |     | -100|     |
% X     +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     6 | -100| -100| -100| -100|     | -100| -100|     | -100|     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     7 |     |     |     | -100|     | -100|     |     | -100|     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     8 |     | -100|     | -100|     | -100|     | -100| -100|     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     9 |     | -100|     | -100|     | -100|     |     |     |     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%    10 |     | -100|     |     |     | -100|     | -100| -100|     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%          1     2     3     4     5     6     7     8     9     10

pen = -100;
rew = 100;

pattern = zeros(10, 10, 3);
pattern(:, :, 2) = [   0,   0,   0,   0,   0,   0,   0,   0, pen, rew ;
                       0, pen, pen, pen, pen, pen, pen,   0, pen,   0 ;
                       0, pen,   0,   0,   0,   0, pen,   0, pen,   0 ;
                       0, pen, pen,   0, pen, pen, pen,   0, pen,   0 ;
                       0,   0,   0,   0,   0, pen,   0,   0, pen,   0 ;
                     pen, pen, pen, pen,   0, pen, pen,   0, pen,   0 ;
                       0,   0,   0, pen,   0, pen,   0,   0, pen,   0 ;
                       0, pen,   0, pen,   0, pen,   0, pen, pen,   0 ;
                       0, pen,   0, pen,   0, pen,   0,   0,   0,   0 ;
                     NaN, pen,   0,   0,   0, pen,   0, pen, pen,   0 ];

propr2(m, [10, 1, NaN], 1, pattern, 'nanvalue', 0);

%% Perform Value Iteration
% The choice of the discount factor here is important. If we choose a value that
% is too high, the robot will favor the future reward more than the current
% penalties, and hit the obstacles. For this example, we set the discount factor
% to be 0.5, equally favoring the future reward and the immediate penalties.

m.gamma = 0.5;

[Vi, pol, a] = itervalue(m, 10000, 'AbsTol', 1E-20);

m.policy = pol;

%% Simulate the System
% Now we simulate the robot's action using the current policy.

opts = mdpset(m, 'StateFunction', Xf);

[t, y] = mdpsim(sys, m, [0 100], {[9.5, 0.5, pi]}, 'MdpOptions', opts);

%% Plot the Result
% Plot the result, flipping the Y direction to match our imagined grid.

plot(y{1}(:, 2), y{1}(:, 1));
grid

set(gca, 'YDir', 'reverse')

%%
% We can see that the robot successfully navigates the maze, avoiding all
% obstacles, and spends some time at the end moving in and out of the goal
% state. This is because we defined the reward to apply when we move into the
% goal state by choosing the 'move forward' action. The robot tries to maximize
% this reward by moving in and out of the goal state as many times as possible
% in the time that we have allowed it to run. Of course, we could terminate the
% simulation once the robot reaches the goal, but we show here how the robot
% behaves if the simulation continues to run.

%%
% We can also plot all 3 states simultaneously to visualize the movement of the
% robot with the changes of angle included.
% 
% Movement up and down correspond to changes in the heading of the robot.
plot3(y{1}(:, 1), y{1}(:, 2), y{1}(:, 3));
grid
view(45, 70)
