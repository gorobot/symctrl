classdef test_transfer_function < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testTransferFunctionSetVar(testCase)
            syms s

            sys = transferfunction();
            sys.var = [s];
            testCase.verifyEqual(sys.var, s);

            sys = transferfunction();
            sys.var = {s};
            testCase.verifyEqual(sys.var, s);

            sys = transferfunction();
            sys.var = {'s'};
            testCase.verifyEqual(sys.var, s);
        end
        function testTransferFunctionGetVar(testCase)
            syms s

            sys = transferfunction();
            sys.var = s;

            testCase.verifyEqual(sys.var, s);
        end

        function testTransferFunctionSetNum(testCase)
            syms s

            sys = transferfunction();
            sys.num = [s + 1, s - 1];
            testCase.verifyEqual(sys.num, [s + 1; s - 1]);

            sys = transferfunction();
            sys.num = {s + 1, s - 1};
            testCase.verifyEqual(sys.num, [s + 1; s - 1]);

            sys = transferfunction();
            sys.num = {'s + 1', 's - 1'};
            testCase.verifyEqual(sys.num, [s + 1; s - 1]);
        end
        function testTransferFunctionGetNum(testCase)
            syms s

            sys = transferfunction();
            sys.num = [s + 1, s - 1];

            testCase.verifyEqual(sys.num, [s + 1; s - 1]);
            testCase.verifyEqual(sys.num(1), [s + 1]);
            testCase.verifyEqual(sys.num(2), [s - 1]);
        end

        function testTransferFunctionSetDen(testCase)
            syms s

            sys = transferfunction();
            sys.den = [s + 1, s - 1];
            testCase.verifyEqual(sys.den, [s + 1; s - 1]);

            sys = transferfunction();
            sys.den = {s + 1, s - 1};
            testCase.verifyEqual(sys.den, [s + 1; s - 1]);

            sys = transferfunction();
            sys.den = {'s + 1', 's - 1'};
            testCase.verifyEqual(sys.den, [s + 1; s - 1]);
        end
        function testTransferFunctionGetDen(testCase)
            syms s

            sys = transferfunction();
            sys.den = [s + 1, s - 1];

            testCase.verifyEqual(sys.den, [s + 1; s - 1]);
            testCase.verifyEqual(sys.den(1), [s + 1]);
            testCase.verifyEqual(sys.den(2), [s - 1]);
        end

        function testTransferFunctionAdd(testCase)
            syms s

            sys1 = transferfunction();
            sys1.var = s;
            sys2 = transferfunction();
            sys2.var = s;

            sys1.num = s;
            sys1.den = 1;

            sys2.num = s;
            sys2.den = 1;

            sys1 = sys1 + sys2;
            testCase.verifyEqual(sys1.num, 2*s);
            testCase.verifyEqual(sys1.den, 1);
        end

        function testTransferFunctionMul(testCase)
            syms s

            sys1 = transferfunction();
            sys1.var = s;
            sys2 = transferfunction();
            sys2.var = s;

            sys1.num = s;
            sys1.den = 1;

            sys2.num = s;
            sys2.den = 1;

            sys1 = sys1 * sys2;
            testCase.verifyEqual(sys1.num, s^2);
            testCase.verifyEqual(sys1.den, 1);
        end

        function testTransferFunctionDiv(testCase)
            syms s

            sys1 = transferfunction();
            sys1.var = s;
            sys2 = transferfunction();
            sys2.var = s;

            sys1.num = s;
            sys1.den = 1;

            sys2.num = s^2;
            sys2.den = 1;

            sys1 = sys1/sys2;
            testCase.verifyEqual(sys1.num, s);
            testCase.verifyEqual(sys1.den, s^2);
        end

        function testTransferFunctionPow(testCase)
            syms s

            sys = transferfunction();
            sys.var = s;

            sys.num = s;
            sys.den = 1;

            sys = sys^2;
            testCase.verifyEqual(sys.num, s^2);
            testCase.verifyEqual(sys.den, 1);
        end
    end
end
