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
    end
end
