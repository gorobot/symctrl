classdef test_state_space < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testStateSpaceAddStates(testCase)
            % sym
            syms x1 x2

            sys = statespace();
            sys.states = [x1, x2];
            testCase.verifyEqual(sys.states, [x1; x2]);

            sys = statespace();
            sys.states = [x1; x2];
            testCase.verifyEqual(sys.states, [x1; x2]);

            sys = statespace();
            sys.states = {x1, x2};
            testCase.verifyEqual(sys.states, [x1; x2]);

            sys = statespace();
            sys.states = {'x1', 'x2'};
            testCase.verifyEqual(sys.states, [x1; x2]);

            % symfun
            syms x1(t) x2(t)

            sys = statespace();
            sys.states = [x1, x2];
            testCase.verifyEqual(sys.states, formula([x1; x2]));

            sys = statespace();
            sys.states = [x1; x2];
            testCase.verifyEqual(sys.states, formula([x1; x2]));

            sys = statespace();
            sys.states = {x1, x2};
            testCase.verifyEqual(sys.states, formula([x1; x2]));

            sys = statespace();
            sys.states = {'x1(t)', 'x2(t)'};
            testCase.verifyEqual(sys.states, formula([x1; x2]));
        end
        function testStateSpaceGetStates(testCase)
            syms x1 x2

            sys = statespace();
            sys.states = [x1, x2];

            testCase.verifyEqual(sys.states, [x1; x2]);
            testCase.verifyEqual(sys.states(1), x1);
            testCase.verifyEqual(sys.states(2), x2);
        end
        function testStateSpaceSetStates(testCase)
            syms x1 x2 x3

            sys = statespace();
            sys.states = [x1, x2];

            testCase.verifyEqual(sys.states(1), x1);

            sys.states(1) = x3;
            testCase.verifyEqual(sys.states(1), x3);
            testCase.verifyEqual(sys.states(2), x2);
        end

        function testStateSpaceAddInputs(testCase)
            % sym
            syms u1 u2

            sys = statespace();
            sys.inputs = [u1, u2];
            testCase.verifyEqual(sys.inputs, [u1; u2]);

            sys = statespace();
            sys.inputs = [u1; u2];
            testCase.verifyEqual(sys.inputs, [u1; u2]);

            sys = statespace();
            sys.inputs = {u1, u2};
            testCase.verifyEqual(sys.inputs, [u1; u2]);

            sys = statespace();
            sys.inputs = {'u1', 'u2'};
            testCase.verifyEqual(sys.inputs, [u1; u2]);

            % symfun
            syms u1(t) u2(t)

            sys = statespace();
            sys.inputs = [u1, u2];
            testCase.verifyEqual(sys.inputs, formula([u1; u2]));

            sys = statespace();
            sys.inputs = [u1; u2];
            testCase.verifyEqual(sys.inputs, formula([u1; u2]));

            sys = statespace();
            sys.inputs = {u1, u2};
            testCase.verifyEqual(sys.inputs, formula([u1; u2]));

            sys = statespace();
            sys.inputs = {'u1(t)', 'u2(t)'};
            testCase.verifyEqual(sys.inputs, formula([u1; u2]));
        end
        function testStateSpaceGetInputs(testCase)
            syms u1 u2

            sys = statespace();
            sys.inputs = [u1, u2];

            testCase.verifyEqual(sys.inputs, [u1; u2]);
            testCase.verifyEqual(sys.inputs(1), u1);
            testCase.verifyEqual(sys.inputs(2), u2);
        end
        function testStateSpaceSetInputs(testCase)
            syms u1 u2 u3

            sys = statespace();
            sys.inputs = [u1, u2];

            testCase.verifyEqual(sys.inputs(1), u1);

            sys.inputs(1) = u3;
            testCase.verifyEqual(sys.inputs(1), u3);
            testCase.verifyEqual(sys.inputs(2), u2);
        end

        function testStateSpaceAddStateFunctions(testCase)
            % sym
            syms x1 x2

            sys = statespace();
            sys.f = [x1 + x2, x1 - x2];
            testCase.verifyEqual(sys.f, [x1 + x2; x1 - x2]);

            sys = statespace();
            sys.f = [x1 + x2; x1 - x2];
            testCase.verifyEqual(sys.f, [x1 + x2; x1 - x2]);

            sys = statespace();
            sys.f = {x1 + x2; x1 - x2};
            testCase.verifyEqual(sys.f, [x1 + x2; x1 - x2]);

            sys = statespace();
            sys.f = {'x1 + x2', 'x1 - x2'};
            testCase.verifyEqual(sys.f, [x1 + x2; x1 - x2]);

            % symfun
            syms x1(t) x2(t)

            sys = statespace();
            sys.f = [x1 + x2, x1 - x2];
            testCase.verifyEqual(sys.f, formula([x1 + x2; x1 - x2]));

            sys = statespace();
            sys.f = [x1 + x2; x1 - x2];
            testCase.verifyEqual(sys.f, formula([x1 + x2; x1 - x2]));

            sys = statespace();
            sys.f = {x1 + x2; x1 - x2};
            testCase.verifyEqual(sys.f, formula([x1 + x2; x1 - x2]));

            sys = statespace();
            sys.f = {'x1(t) + x2(t)', 'x1(t) - x2(t)'};
            testCase.verifyEqual(sys.f, formula([x1 + x2; x1 - x2]));
        end
        function testStateSpaceGetStateFunctions(testCase)
            syms x1 x2

            sys = statespace();
            sys.f = [x1 + x2, x1 - x2];
            testCase.verifyEqual(sys.f, [x1 + x2; x1 - x2]);
            testCase.verifyEqual(sys.f(1), x1 + x2);
            testCase.verifyEqual(sys.f(2), x1 - x2);
        end
        function testStateSpaceSetStateFunctions(testCase)
            syms x1 x2

            sys = statespace();
            sys.f = [x1 + x2, x1 - x2];

            testCase.verifyEqual(sys.f(1), x1 + x2);

            sys.f(1) = x1*x2;
            testCase.verifyEqual(sys.f(1), x1*x2);
            testCase.verifyEqual(sys.f(2), x1 - x2);
        end

        function testStateSpaceAddOutputFunctions(testCase)
            % sym
            syms x1 x2

            sys = statespace();
            sys.g = [x1 + x2, x1 - x2];
            testCase.verifyEqual(sys.g, [x1 + x2; x1 - x2]);

            sys = statespace();
            sys.g = [x1 + x2; x1 - x2];
            testCase.verifyEqual(sys.g, [x1 + x2; x1 - x2]);

            sys = statespace();
            sys.g = {x1 + x2; x1 - x2};
            testCase.verifyEqual(sys.g, [x1 + x2; x1 - x2]);

            sys = statespace();
            sys.g = {'x1 + x2', 'x1 - x2'};
            testCase.verifyEqual(sys.g, [x1 + x2; x1 - x2]);

            % symfun
            syms x1(t) x2(t)

            sys = statespace();
            sys.g = [x1 + x2, x1 - x2];
            testCase.verifyEqual(sys.g, formula([x1 + x2; x1 - x2]));

            sys = statespace();
            sys.g = [x1 + x2; x1 - x2];
            testCase.verifyEqual(sys.g, formula([x1 + x2; x1 - x2]));

            sys = statespace();
            sys.g = {x1 + x2; x1 - x2};
            testCase.verifyEqual(sys.g, formula([x1 + x2; x1 - x2]));

            sys = statespace();
            sys.g = {'x1(t) + x2(t)', 'x1(t) - x2(t)'};
            testCase.verifyEqual(sys.g, formula([x1 + x2; x1 - x2]));
        end
        function testStateSpaceGetOutputFunctions(testCase)
            syms x1 x2

            sys = statespace();
            sys.g = [x1 + x2, x1 - x2];
            testCase.verifyEqual(sys.g, [x1 + x2; x1 - x2]);
            testCase.verifyEqual(sys.g(1), x1 + x2);
            testCase.verifyEqual(sys.g(2), x1 - x2);
        end
        function testStateSpaceSetOutputFunctions(testCase)
            syms x1 x2

            sys = statespace();
            sys.g = [x1 + x2, x1 - x2];

            testCase.verifyEqual(sys.g(1), x1 + x2);

            sys.g(1) = x1*x2;
            testCase.verifyEqual(sys.g(1), x1*x2);
            testCase.verifyEqual(sys.g(2), x1 - x2);
        end

        function testStateSpaceGetABCDMatrix(testCase)
            % sym
            syms x1 x2 u

            sys = statespace();
            sys.states = [x1; x2];
            sys.inputs = u;
            sys.f = [x2, -sin(x1) - x2 + u];
            sys.g = x1;

            testCase.verifyEqual(sys.A, [0, 1; -cos(x1), -1]);
            testCase.verifyEqual(sys.B, [0; 1]);
            testCase.verifyEqual(sys.C, [1, 0]);
            testCase.verifyEqual(sys.D, 0);

            % symfun
            syms x1(t) x2(t) u(t)

            sys = statespace();
            sys.states = [x1; x2];
            sys.inputs = u;
            sys.f = [x2, -sin(x1) - x2 + u];
            sys.g = x1;

            testCase.verifyEqual(sys.A, formula([0, 1; -cos(x1), -1]));
            testCase.verifyEqual(sys.B, [0; 1]);
            testCase.verifyEqual(sys.C, [1, 0]);
            testCase.verifyEqual(sys.D, 0);
        end

        function testStateSpaceLinearize(testCase)
            syms x1 x2 u
            sys = statespace();
            sys.states = [x1; x2];
            sys.inputs = u;
            sys.f = [x2, -sin(x1) - x2 + u];
            sys.g = x1;

            sys.linearize();

            testCase.verifyEqual(sys.A, [0, 1; -1, -1]);
            testCase.verifyEqual(sys.B, [0; 1]);
            testCase.verifyEqual(sys.C, [1, 0]);
            testCase.verifyEqual(sys.D, 0);
        end

        function testStateSpaceControllability(testCase)
            syms x1 x2 u
            sys = statespace();
            sys.states = [x1; x2];
            sys.inputs = u;
            sys.f = [x2, -sin(x1) - x2 + u];
            sys.g = x1;

            testCase.verifyEqual(ctrb(sys), [0, 1; 1, -1]);
        end

        function testStateSpaceObservability(testCase)
            syms x1 x2 u
            sys = statespace();
            sys.states = [x1; x2];
            sys.inputs = u;
            sys.f = [x2, -sin(x1) - x2 + u];
            sys.g = x1;

            testCase.verifyEqual(obsv(sys), [1, 0; 0, 1]);
        end

        function testStateSpaceRandomVariables(testCase)
            w1 = randomvar('w1', randomdistribution.Normal, 0, 1);
            w2 = randomvar('w2', randomdistribution.Normal, 0, 1);

            syms x1 x2 u
            sys = statespace();
            sys.states = [x1; x2];
            sys.inputs = u;
            sys.f = [x2 + w1.sym(), -sin(x1) - x2 + u + w2.sym()];
            sys.g = x1;
        end
    end
end
