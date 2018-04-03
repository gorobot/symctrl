%% Quadrotor Example
% Example of analysis of a quadrotor system.

sys = ctrldemo('quadrotor');

C = {g == 9.8;
     m == 0.5;
     l == 0.1;
     Jx == 1;
     Jy == 1;
     Jz == 1;
     b == 1;
     d == 1};

linsys = linearize(sys|C);

%%

% lsim(linsys, sym(1), [0 10], ...
%     {[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10], ...
%      [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5]});
 
step(linsys, [0 20], ...
    {[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10], ...
     [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5]});

%%
roa(linsys)

%%
motor2torque = @(w1, w2, w3, w4) ...
    [b*(w1^2 + w2^2 + w3^2 + w4^2), ...
     b*l*(w3^2 - w1^2), ...
     b*l*(w4^2 - w2^2), ...
     d*(w2^2 + w4^2 - w1^2 - w3^2)];

% inputs = [ft, tx, ty, tz];
inputs = motor2torque(1, 1, 1, 1);
