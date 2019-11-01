classdef test_ode < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testOdeEulerMethod(testCase)
            syms x

            sys = statespace();
            sys.states = x;
            sys.f = 2*x + 1;

            [t, y] = ode_euler(sys, [0, 0.1], 1);

            testCase.verifyEqual(t(1), 0, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(1), 1, 'AbsTol', 1E-3);
            testCase.verifyEqual(t(101), 0.1, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(101), 1.3317, 'AbsTol', 1E-3);
        end

        function testOdeEulerMethodPendulum(testCase)
            syms x1 x2

            sys = statespace();
            sys.states = [x1 x2];
            sys.f = [x2, -sin(x1) - x2];

            [t, y] = ode_euler(sys, [0 20], [4 0]);

            testCase.verifyEqual(t(1), 0, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(1, 1), 4, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(1, 2), 0, 'AbsTol', 1E-3);
            testCase.verifyEqual(t(20001), 20, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(20001, 1), 6.283, 'AbsTol', 1E-3);
            testCase.verifyEqual(y(20001, 2), 0, 'AbsTol', 1E-3);
        end

        function testOdeRandomVariables(testCase)
            w1 = randomvar('w1', randomdistribution.Normal, 0, 1);
            w2 = randomvar('w2', randomdistribution.Normal, 0, 1);

            syms x1 x2

            sys = statespace();
            sys.states = [x1 x2];
            sys.f = [x2 + w1.sym(), -sin(x1) - x2 + w2.sym()];

            [t, y] = ode_euler(sys, [0 20], [4 0]);
        end
    end
end
