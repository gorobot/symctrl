classdef dareTest < matlab.unittest.TestCase
    %DARETEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testDare1(testCase)
            % should return a solution to the discrete ARE.
            A = [1 -1 1; 0 1 1; 0 0 1];
            B = [1 0; 1 0; 0 1];

            Q = diag([10 1 0.1]);
            R = diag([10 0.1]);

            syms x1 x2 x3 u1 u2
            sys = symss;
            sys.states = [x1, x2, x3];
            sys.inputs = [u1, u2];

            sys.f = A*sys.states + B*sys.inputs;
            [P, K] = dare(sys, Q, R);
            
            verP = [   42.2835  -68.5247   -3.9478
                      -68.5247  154.0431   16.0017
                       -3.9478   16.0017    8.3320 ];
            verK = [   -0.3958    1.5994    0.8106
                        0.0976    0.0796    1.2589 ];
            
            testCase.verifyEqual(double(P), verP, 'AbsTol', 1E-3);
            testCase.verifyEqual(double(K), verK, 'AbsTol', 1E-3);
        end
        
        function testDare2(testCase)
            % should return a solution to the discrete ARE.
            A = [1 3; 1 2];
            B = [1; -2];
            
            Q = diag([0.2, 1]);
            R = 0.5;

            syms x1 x2 u
            sys = symss;
            sys.states = [x1, x2];
            sys.inputs = u;

            sys.f = A*sys.states + B*sys.inputs;
            [P, K] = dare(sys, Q, R);
            
            verP = [    1.6276    3.6763
                        3.6763   10.5101 ];
            verK = [   -0.7830   -1.7603 ];
            
            testCase.verifyEqual(double(P), verP, 'AbsTol', 1E-3);
            testCase.verifyEqual(double(K), verK, 'AbsTol', 1E-3);
        end
        
        function testDare3(testCase)
            % should return a solution to the discrete ARE.
            A = [0 2; 1 1];
            B = [0; 1];
            
            Q = [2.25, -1.5; -1.5, 1];
            R = 2;

            syms x1 x2 u
            sys = symss;
            sys.states = [x1, x2];
            sys.inputs = u;

            sys.f = A*sys.states + B*sys.inputs;
            [P, K] = dare(sys, Q, R);
            
            verP = [    4.0611    0.3835
                        0.3835   19.1725 ];
            verK = [    0.9055    0.9418 ];
            
            testCase.verifyEqual(double(P), verP, 'AbsTol', 1E-3);
            testCase.verifyEqual(double(K), verK, 'AbsTol', 1E-3);
        end
    end
end

