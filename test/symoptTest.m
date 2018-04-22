classdef symoptTest < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testSymoptCreation(testCase)
            % should be able to create a symopt.
            syms f0(x) f1(x) f2(x) h1(x) h2(x)
            opt = symopt(f0);
            opt.st(1) = f1 <= 0;
            opt.st(2) = f2 <= 0;
            opt.st(3) = h1 == 0;
            opt.st(4) = h2 == 0;
            
            testCase.verifyEqual(opt.f, f0(x));
            testCase.verifyNumElements(opt.vars, 1);
            testCase.verifyNumElements(opt.st, 4);
        end
        
        function testSymoptSolver(testCase)
            % should be able to solve an unconstrained symopt.
            syms x1 x2
            opt = symopt(x1^2 + x1*x2 + 3*x2^2);
            
            S = symoptsolve(opt, 'gd', [3, 3], 1E-3);
            testCase.verifyEqual(double(struct2array(S)), [0, 0], 'AbsTol', 1E-2);
            
            S = symoptsolve(opt, 'gd', [3, 3], 1E-5);
            testCase.verifyEqual(double(struct2array(S)), [0, 0], 'AbsTol', 1E-4);
            
            S = symoptsolve(opt, 'gd', [3, 3], 1E-7);
            testCase.verifyEqual(double(struct2array(S)), [0, 0], 'AbsTol', 1E-6);
        end
    end
end

