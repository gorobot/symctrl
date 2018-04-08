classdef lyapTest < matlab.unittest.TestCase
    %LYAPTEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testLyapFunctionNumeric(testCase)
            % should find a Lyapunov function for a numeric system.
            syms x1 x2
            sys = symss;
            sys.states = [x1, x2];
            
            A = [0, 1; -6, -5];
            
            sys.f = A*sys.states;
            
            Q = eye(size(A));
            P = lyap(sys, Q);
            
            testCase.verifyTrue(islyap(P, Q));
        end
        
        function testLyapFunctionNumericDefective(testCase)
            % should find a Lyapunov function for a defective matrix.
            syms x1 x2 x3 x4 x5
            sys = symss;
            sys.states = [x1, x2, x3, x4, x5];
            
            A = [ 1  0  0  0  0; 
                  3  1  0  0  0; 
                  6  3  2  0  0; 
                 10  6  3  2  0;
                 15 10  6  3  2];
             
            sys.f = A*sys.states;
            
            Q = eye(size(A));
            P = lyap(sys, Q);
            
            testCase.verifyTrue(islyap(P, Q));
        end
        
        function testLyapFunctionSymbolicNonlinear1(testCase)
            % should find a symbolic Lyapunov function for a linearized
            % system.
            sys = ctrldemo('pendulum2');
            sys = linearize(sys);
            
            Q = eye(size(sys.A));
            P = lyap(sys, Q);
            
            testCase.verifyTrue(islyap(P, Q));
        end
        
        function testLyapFunctionSymbolicNonlinear2(testCase)
            % should find a symbolic Lyapunov function for a linearized
            % system.
            syms x1 x2
            sys = symss;
            sys.states = [x1, x2];
            sys.f(1) = 3*x2;
            sys.f(2) = -5*x1 + x1^3 - 2*x2;
            
            sys = linearize(sys);
            
            Q = eye(size(sys.A));
            P = lyap(sys, Q);
            
            testCase.verifyTrue(islyap(P, Q));
        end
    end
end

