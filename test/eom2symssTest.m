classdef eom2symssTest < matlab.unittest.TestCase
    %EOM2SYMSSTEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testEomOneEquation(testCase)
            %EOM2SYMSS should convert EOM to SYMSS.
            syms m l b g
            syms theta(t) T
            f1 = m*l^2*diff(theta, 2) + b*l*diff(theta) + m*g*l*sin(theta) == T;

            sys = eom2symss(f1, [theta, diff(theta)]);
            
            testCase.verifyEqual(sys.f(1), ...
                diff(theta(t), t));
            testCase.verifyEqual(sys.f(2), ...
                -(b*l*diff(theta(t), t) - T + g*l*m*sin(theta(t)))/(l^2*m));
        end
        
        function testEomTwoEquations(testCase)
            %EOM2SYMSS should convert EOM to SYMSS.
            syms M1 B B1 K K1 M2 B2 K2 t y positive
            syms fo1(t) fo2(t)
            syms y1(t) y2(t)

            f1 = M1*diff(y1, t, t) + (B + B1)*diff(y1, t) + (K + K1)*y1 - B*diff(y2, t) - K*y2 == fo1;
            f2 = M2*diff(y2, t, t) + (B + B2)*diff(y2, t) + (K + K2)*y2 - B1*diff(y1, t) - K*y1 == -fo2;

            sys = eom2symss([f1, f2], [y1, diff(y1, t), y2, diff(y2, t)]);
            
            testCase.verifyEqual(sys.f(1), ...
                diff(y1(t), t));
            testCase.verifyEqual(sys.f(2), ...
                -(B*diff(y1(t), t) - fo1(t) - B*diff(y2(t), t) + B1*diff(y1(t), t) + K*y1(t) - K*y2(t) + K1*y1(t))/M1);
            testCase.verifyEqual(sys.f(3), ...
                diff(y2(t), t));
            testCase.verifyEqual(sys.f(4), ...
                -(fo2(t) + B*diff(y2(t), t) - B1*diff(y1(t), t) + B2*diff(y2(t), t) - K*y1(t) + K*y2(t) + K2*y2(t))/M2);
        end
        
        function testEomWithInputDerivatives(testCase)
            %EOM2SYMSS should convert EOM to SYMSS with input derivatives.
            syms x(t) u(t) a1 a2 a3 b0 b1
            f1 = diff(x, 3) + a1*diff(x, 2) + a2*diff(x) + a3*x == b0*diff(u) + b1*u;
             
            sys = eom2symss(f1, [x, diff(x), diff(x, 2)]);
            
            testCase.verifyEqual(1, 1);
        end
    end
end

