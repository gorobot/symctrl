classdef careTest < matlab.unittest.TestCase
    %CARETEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testCare1(testCase)
            % should return a solution to the continuous ARE.
            A = [-3, 2; 1, 1];
            B = [0; 1];
            
            Q = [1, -1; -1, 1];
            R = 3;
            
            syms x1 x2 u
            sys = symss;
            sys.states = [x1, x2];
            sys.inputs = u;
            
            sys.f = A*sys.states + B*sys.inputs;
            [P, K] = care(sys, Q, R);
            
            verP = [    0.5895    1.8216
                        1.8216    8.8188 ];
            verK = [    0.6072    2.9396 ];
            
            testCase.verifyEqual(double(P), verP, 'AbsTol', 1E-3);
            testCase.verifyEqual(double(K), verK, 'AbsTol', 1E-3);
        end
        
        function testCare2(testCase)
            % should return a solution to the continuous ARE.
            A = [0, 1; 0, 0];
            B = [0; 1];

            Q = [1, 0; 0, 1];
            R = 1;

            syms x1 x2 u
            sys = symss;
            sys.states = [x1, x2];
            sys.inputs = u;

            sys.f = A*sys.states + B*sys.inputs;
            [P, K] = care(sys, Q, R);
            
            verP = [    1.7321    1.0000
                        1.0000    1.7321 ];
            verK = [    1.0000    1.7321 ];
            
            testCase.verifyEqual(double(P), verP, 'AbsTol', 1E-3);
            testCase.verifyEqual(double(K), verK, 'AbsTol', 1E-3);
        end
    end
end

