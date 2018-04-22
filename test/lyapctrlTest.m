classdef lyapctrlTest < matlab.unittest.TestCase
    %LYAPCTRLTEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testCtrllyapNonlinear1(testCase)
            % should compute a control input.
            syms x u a b
            sys = symss;
            sys.states = x;
            sys.inputs = u;

            sys.f(1) = a*x - b*x^3 + u;
            sys.g(1) = x;

            V = x^2/2;

            U = lyapctrl(sys, V);
            
            ref = -(x*(- b*x^3 + a*x) + ...
                  (x^2*(- b*x^3 + a*x)^2 + x^4)^(1/2))/x;
            
            testCase.verifyEqual(U, ref);
        end
        
        function testCtrllyapNonlinear2(testCase)
            % should compute a control input.
            syms x1 x2 u
            sys = symss;
            sys.states = [x1 x2];
            sys.inputs = u;

            sys.f(1) = x2;
            sys.f(2) = -x1 + x1*u;

            V = x1^2/2 + x2^2/2;

            U = lyapctrl(sys, V);
            % Note that in literature, the input is defined as -x1*x2. We
            % can achieve this if we specify that x1 & x2 are real and
            % simplify the expression.
            ref = -(x1^4*x2^4)^(1/2)/(x1*x2);
            
            testCase.verifyEqual(U, ref);
        end
    end
end

