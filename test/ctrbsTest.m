classdef ctrbsTest < matlab.unittest.TestCase
    %CTRBSTEST Summary of this class goes here
    %   Detailed explanation goes here

    methods (Test)
        function testCtrbs(testCase)
            % should compute the controllability matrix.
            A = [1  1; 4 -2];
            B = [1 -1; 1 -1];

            Co = ctrbs(A, B);

            verCo = [     1    -1     2    -2
                          1    -1     2    -2 ];

            testCase.verifyEqual(Co, sym(verCo));
        end

        function testObsvs(testCase)
            % should compute the observability matrix.
            A = [1  1; 4 -2];
            C = [1  0; 0  1];

            Ob = obsvs(A, C);

            verOb = [ 1     0
                      0     1
                      1     1
                      4    -2 ];

            testCase.verifyEqual(Ob, sym(verOb));
        end
    end
end
