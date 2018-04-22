%% Kalman Decomposition Example
% Example showing the Kalman decomposition of a reducible system.

%% System With Uncontrollable States
A = [   0   0   0   0;
        0  -2   0   0;
      2.5 2.5  -1   0; 
      2.5 2.5   0  -3];

B = [   1;
        1; 
        0; 
        0];
   
C = [   0   0   1   1];

D = 0;

sys = symss(A, B, C, D);

T = canon(sys, 'k');

%% System With Uncontrollable and Unobservable States
A = [   2   1  -1   0   0   0; 
        5  -1  10  -7   0   0; 
        1   0   3  -1   0   0; 
       -2   3  -7   6   0   0; 
       -3   2  -4   1   5   1;
       -2   6 -18   8   0   6];

B = [   1   2;
        0   5; 
        1   2; 
        2   1; 
        1   1; 
        1   1];

C = [   0   0   0   1   0   0;
       -1   2  -6   3   0   1];

D = zeros(2);

sys = symss(A, B, C, D);

% T = canon(sys, 'k');
T = decompose(sys)
