classdef test_symctrl < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testMat2Se(testCase)
            se = symctrl.mat2se({'a'});
            testCase.verifyEqual(se, {'a'});

            se = symctrl.mat2se('a');
            testCase.verifyEqual(se, {'a'});

            se = symctrl.mat2se({'a', 'b'});
            testCase.verifyEqual(se, {'a', 'b'});

            se = symctrl.mat2se("a");
            testCase.verifyEqual(se, {'a'});

            se = symctrl.mat2se(["a", "b"]);
            testCase.verifyEqual(se, {'a', 'b'});

            a = sym('a');
            b = sym('b');

            se = symctrl.mat2se(a);
            testCase.verifyEqual(se, {'a'});

            se = symctrl.mat2se({a, b});
            testCase.verifyEqual(se, {'a', 'b'});

            se = symctrl.mat2se([a, b]);
            testCase.verifyEqual(se, {'a', 'b'});
        end

        function testGetsymdiff(testCase)
            syms a(t) b c(t)

            testCase.verifyEqual(symctrl.getsymdiff(diff(a)+b), formula(diff(a)));
            testCase.verifyEqual(symctrl.getsymdiff(diff(a)-b), formula(diff(a)));
            testCase.verifyEqual(symctrl.getsymdiff(diff(a)*b), formula(diff(a)));
            testCase.verifyEqual(symctrl.getsymdiff(diff(a)/b), formula(diff(a)));

            testCase.verifyEqual(symctrl.getsymdiff(diff(a)+c), formula(diff(a)));
            testCase.verifyEqual(symctrl.getsymdiff(diff(a)-c), formula(diff(a)));
            testCase.verifyEqual(symctrl.getsymdiff(diff(a)*c), formula(diff(a)));
            testCase.verifyEqual(symctrl.getsymdiff(diff(a)/c), formula(diff(a)));
        end

        function testGetsymfuns(testCase)
            syms a(t) b c(t)

            testCase.verifyEqual(symctrl.getsymfuns(b+a), a(t));
            testCase.verifyEqual(symctrl.getsymfuns(b-a), a(t));
            testCase.verifyEqual(symctrl.getsymfuns(b*a), a(t));
            testCase.verifyEqual(symctrl.getsymfuns(b/a), a(t));

            testCase.verifyEqual(symctrl.getsymfuns(a+c), [a(t), c(t)]);
            testCase.verifyEqual(symctrl.getsymfuns(a-c), [a(t), c(t)]);
            testCase.verifyEqual(symctrl.getsymfuns(a*c), [a(t), c(t)]);
            testCase.verifyEqual(symctrl.getsymfuns(a/c), [a(t), c(t)]);
        end
    end
end
