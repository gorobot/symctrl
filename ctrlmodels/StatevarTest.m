classdef StatevarTest < matlab.unittest.TestCase
    %UNTITLED8 Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testStatevarCreation(testCase)
            % statevar should be instantiable.
            a = statevar('a');
            testCase.verifyInstanceOf(a, 'statevar');
            
            b = sym('b');
            c = statevar(b);
            testCase.verifyInstanceOf(c, 'statevar');
        end
        
        function testStatevarArrayCreation(testCase)
            % statevar should be instantiable as an array.
            a = statevar(zeros([1 2]));
            testCase.verifyInstanceOf(a, 'statevar');
            testCase.verifyNumElements(a, 2);
            
            b = sym('b', [1 2]);
            c = statevar(b);
            testCase.verifyInstanceOf(c, 'statevar');
            testCase.verifyNumElements(c, 2);
        end
        
        function testStatevarFunctionCreation(testCase)
            % statevar should be instantiable as a function.
            a = statevar('c(t)');
            testCase.verifyInstanceOf(a, 'statevar');
            
            syms t
            
            b = symfun('b(t)', t);
            c = statevar(b);
            testCase.verifyInstanceOf(c, 'statevar');
            
            d = symfun(t+1, t);
            f = statevar(d);
            testCase.verifyInstanceOf(f, 'statevar');
        end
        
        function testStatevarArrayConcatenation(testCase)
            % statevar underlying array should be indexable.
            a = statevar(zeros([2 2]));
            b = statevar(zeros([2 2]));
            
            x = [a b];
            testCase.verifyInstanceOf(x, 'statevar');
            testCase.verifySize(x, [2 4]);
            
            x = [a; b];
            testCase.verifyInstanceOf(x, 'statevar');
            testCase.verifySize(x, [4 2]);
        end
        
        function testStatevarFunctionEvaluation(testCase)
            % statevar function should be possible to evaluate.
            syms a(t)
            b = statevar(a);
            testCase.verifyEqual(a(1), b(1));
            
            t = sym('t');
            c = symfun(t+1, t);
            d = statevar(c);
            testCase.verifyEqual(c(1), d(1));
        end
        
        function testStatevarFunctionDerivative(testCase)
            % statevar function should be possible to differentiate.
            a = statevar('a');
            testCase.verifyEqual(diff(a), sym(1));
            
            b = statevar('b(t)');
            testCase.verifyNotEqual(diff(b), sym(1));
        end
        
        function testStatevarFunctionAsParameter(testCase)
            % statevars should be able to be passed as parameters to
            % symbolic functions.
            syms t
            
            x1 = statevar('x1');
            x2 = statevar('x2');
            x = [x1 x2];
            x = sym(x);
            
            f1(t, x) = x1 + x2;
            testCase.verifyEqual(1, 1);
        end
    end
end

