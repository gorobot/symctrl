classdef symhyssTest < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods (Test)
        function testSystemCreationEmpty(testCase)
            % should be able to create an empty hybrid system model.
            syms x1 x2
            sys = symhyss;

            testCase.verifyNumElements(sys.states, 0);
            testCase.verifyNumElements(sys.inputs, 0);
        end

        function testSystemCreationWithVariables(testCase)
            % should be able to create a hybrid system model with variables.
            syms x1 x2 x3 u1
            sys = symhyss([x1, [x2, x3]], u1);

            testCase.verifyNumElements(sys.states, 3);
            testCase.verifyNumElements(sys.inputs, 1);
        end

        function testSetVariablesAfterCreation(testCase)
            % should be able to define state variables after construction.
            syms x1 x2 x3 u1
            sys = symhyss;
            sys.states = [x1, [x2, x3]];
            sys.inputs = u1;

            testCase.verifyNumElements(sys.states, 3);
            testCase.verifyNumElements(sys.inputs, 1);
        end

        function testHybridModesCustomIndexing(testCase)
            syms x
            sys = symhyss;
            sys.states = x;

            sys.f(1, 1) = 1;
        end

        function testSetModes(testCase)
            syms x
            sys = symhyss;
            sys.states = x;

            sys.f(1, 1) = 5*x;
            sys.f(2, 1) = -x;

            testCase.verifyEqual(sys.f(1, 1), 5*x);
            testCase.verifyEqual(sys.f(2, 1), -x);
        end
    end
end
