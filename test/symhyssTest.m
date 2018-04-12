classdef symhyssTest < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testSystemCreation(testCase)
            % should be able to pass state variables to constructor.
            syms x1 x2 x3 u1
            sys = symhyss([x1, [x2, x3]], u1);
            
            testCase.verifyNumElements(sys.states, 3);
            testCase.verifyNumElements(sys.inputs, 1);
        end
        
        function testNestedStateVariables(testCase)
            % should be able to define state variables after construction.
            syms x1 x2 x3 u1
            sys = symhyss;
            sys.states = [x1, [x2, x3]];
            sys.inputs = u1;
            
            testCase.verifyNumElements(sys.states, 3);
            testCase.verifyNumElements(sys.inputs, 1);
        end
    end
end

