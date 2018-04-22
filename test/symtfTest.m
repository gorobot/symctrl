classdef symtfTest < matlab.unittest.TestCase
    %SYMTFTEST Summary of this class goes here
    %   Detailed explanation goes here

    methods (Test)
        function testTransferFunctionCreationEmpty(testCase)
            % should be able to create empty transfer functions.
            G = symtf;
            testCase.verifyEqual(G.tf, sym(1));
        end

        function testTransferFunctionCreationWithVariables(testCase)
            % should be able to create transfer functions using symbolic
            % variables.
            syms s
            G = symtf(1/s);
            testCase.verifyEqual(G.tf, 1/s);
        end

        function testTransferFunctionCreationNumDen(testCase)
            % should be able to create transfer functions using
            % coefficients.
            syms s
            G = symtf([1 0], [1 0 0]);
            testCase.verifyEqual(G.tf, 1/s);
            testCase.verifyEqual(G.Numerator, s);
            testCase.verifyEqual(G.Denominator, s^2);
        end

        function testAddingTransferFunctions(testCase)
            % should be able to add transfer functions together.
            syms s
            G1 = symtf(1/s);
            G2 = symtf(2/s);
            G3 = G1 + G2;
            testCase.verifyEqual(G3.tf, 3/s);
            testCase.verifyEqual(G3.Numerator, 3*s);
            testCase.verifyEqual(G3.Denominator, s^2);
        end

        function testTransferFunctionsWithOtherVariables(testCase)
            % should be able to incorporate other variables into tf.
            syms s a
            G = symtf([1 a], [1 1]);
            testCase.verifyEqual(G.Numerator, s+a);
            testCase.verifyEqual(G.Denominator, s+1);
        end

        function testTransferFunctionToStateSpace(testCase)
            % should be able to convert a transfer function to state space
            % when order(num) < order(den).
            syms s
            G = symtf(((s+5)*(s+4))/((s+1)*(s+2)*(s+3)));
            sys = symtf2symss(G);

            testCase.verifyEqual(sys.A, sym([0 1 0; 0 0 1; -6 -11 -6]));
        end

        function testTransferFunctionToStateSpace2(testCase)
            % should be able to convert a transfer function to state space
            % when roots are complex.
            syms s
            G = symtf((4/(s+1-1i))+(4/(s+1+1i))+(2/(s+5))+(3/(s+10)));
            sys1 = symtf2symss(G);

            A = [-5 0 0 0; 0 -10 0 0; 0 0 0 1; 0 0 -2 -2];
            B = [1; 1; 0; 1];
            C = [2 3 8 8];
            D = 0;
            sys2 = symss(A, B, C, D);

            sys2 = canon(sys2);

            testCase.verifyEqual(eig(sys1.A), eig(sys2.A));
        end

        function testTransferFunctionCreationAsVar(testCase)
            % should be able to create a transfer function using the tf as
            % a varaible.
            syms m k b
            G = symtf([b/m 0], [1 b/m k/m]);

            s = symtf('s');
            s = ((b/m)*s)/(s^2 + (b/m)*s + (k/m));

            testCase.verifyEqual(simplify(G.tf), simplify(s.tf));
        end
    end
end
