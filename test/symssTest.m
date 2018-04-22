classdef symssTest < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods (Test)
        function testSystemCreationEmpty(testCase)
            % should be able to create an empty state-space model.
            syms x1 x2
            sys = symss;

            testCase.verifyNumElements(sys.states, 0);
            testCase.verifyNumElements(sys.states, 0);
        end

        function testSystemCreationWithVariables(testCase)
            % should be able to create a state-space model with variables.
            syms x1 x2 u1
            sys1 = symss([x1 x2], u1);

            testCase.verifyNumElements(sys1.states, 2);
            testCase.verifyNumElements(sys1.inputs, 1);

            sys2 = symss(x1);

            testCase.verifyNumElements(sys2.states, 1);
        end

        function testSystemCreationWithNestedStateVariables(testCase)
            % should be able to define state variables after construction.
            syms x1 x2 x3 u1
            sys = symss([x1, [x2, x3]], u1);

            testCase.verifyNumElements(sys.states, 3);
            testCase.verifyNumElements(sys.inputs, 1);
        end

        function testSetVariablesAfterCreation(testCase)
            % should be able to define state variables after construction.
            syms x1 x2 x3 u1
            sys = symss;
            sys.states = [x1, [x2, x3]];
            sys.inputs = u1;

            testCase.verifyNumElements(sys.states, 3);
            testCase.verifyNumElements(sys.inputs, 1);
        end

        function testSystemCreationWithABCD(testCase)
            % should be able to pass matrices to constructor.
            sys = symss([1 0; 0 1], [0; 0], [1 0], 0);

            testCase.verifyNumElements(sys.states, 2);
            testCase.verifyNumElements(sys.inputs, 0);
        end

        function testSystemCreationWithTs(testCase)
            % should be able to pass matrices to constructor.
            sys = symss(1);

            testCase.verifyEqual(sys.Ts, 1);

            sys.Ts = 5;

            testCase.verifyEqual(sys.Ts, 5);
        end

        function testStateSpaceToTransferFunctionConversion(testCase)
            % should convert transfer function to state space
            sys1 = symss([0 1 0; 0 0 1; -1 -2 -3], [0; 0; 1], [1 0 0], 0);

            G = symss2symtf(sys1);

            sys2 = symtf2symss(G);

            testCase.verifyEqual(sys1.A, sys2.A);
        end
    end
end
