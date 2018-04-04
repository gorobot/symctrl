classdef schursTest < matlab.unittest.TestCase
    %SCHURSTEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testSchurDecomposition1(testCase)
            % SCHURS should produce the same result as the built-in SCHUR
            % function.
            X = [2, 2; 0, 2];
            
            [U1, T1] = schur(X);
            [U1, T1] = ordschur(U1, T1, 'lhp');
            
            [U2, T2] = schurs(X);
            
            U2 = double(U2);
            T2 = double(T2);
            
            testCase.verifyEqual(abs(U1), abs(U2), 'AbsTol', 1E-2);
            testCase.verifyEqual(abs(T1), abs(T2), 'AbsTol', 1E-2);
        end
        
        function testSchurDecomposition2(testCase)
            % SCHURS should produce the same result as the built-in SCHUR
            % function.
            X = [-83, 4, 35; -348, 20, 140; -174, 8, 74];
            
            [U1, T1] = schur(X);
            [U1, T1] = ordschur(U1, T1, 'lhp');
            
            [U2, T2] = schurs(X);
            
            U2 = double(U2);
            T2 = double(T2);
            
            testCase.verifyEqual(abs(U1), abs(U2), 'AbsTol', 1E-2);
            testCase.verifyEqual(abs(T1), abs(T2), 'AbsTol', 1E-2);
        end
        
        function testSchurDecomposition3(testCase)
            % SCHURS should produce the same result as the built-in SCHUR
            % function.
            X = [-149, -50, -154; 537, 180, 546; -27, -9, -25];
            
            [U1, T1] = schur(X);
            [U1, T1] = ordschur(U1, T1, 'lhp');
            
            [U2, T2] = schurs(X);
            
            U2 = double(U2);
            T2 = double(T2);
            
            testCase.verifyEqual(abs(U1), abs(U2), 'AbsTol', 1E-2);
            testCase.verifyEqual(abs(T1), abs(T2), 'AbsTol', 1E-2);
        end
        
        function testSchurDecomposition4(testCase)
            % SCHURS should produce the same result as the built-in SCHUR
            % function.
            X = [1, 3, 4; 3, 1, 2; 4, 2, 1];
            
            [U1, T1] = schur(X);
            [U1, T1] = ordschur(U1, T1, 'lhp');
            
            [U2, T2] = schurs(X);
            
            U2 = double(U2);
            T2 = double(T2);
            
            testCase.verifyEqual(abs(U1), abs(U2), 'AbsTol', 1E-2);
            testCase.verifyEqual(abs(T1), abs(T2), 'AbsTol', 1E-2);
        end
        
    end
end

