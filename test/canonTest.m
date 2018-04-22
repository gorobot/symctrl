classdef canonTest < matlab.unittest.TestCase
    %CANONTEST Test canon function.
    
    properties
        system1
    end
    
    methods(TestMethodSetup)
        function loadSystems(testCase)
            % Demo systems.
            A = [0, 1; -2, -3];
            B = [0; 1];
            C = [3, 1];
            D = 0;
            
            testCase.system1 = symss(A, B, C, D);
        end
    end
    
    methods (Test)
        function testControllableCanonicalForm(testCase)
            % should convert state space to controllable canonical form.
            sys = ctrldemo('massspring');
            
            T1 = canon(testCase.system1, 'c');
            T2 = canon(sys, 'c');
            
            testCase.verifyEqual(T1.A, sym([0, 1; -2, -3]));
            testCase.verifyEqual(T1.B, sym([0; 1]));
            testCase.verifyEqual(T1.C, sym([3, 1]));
            
            testCase.verifyEqual(T2.A, sym([0, 1; -K/M, -C/M]));
            testCase.verifyEqual(T2.B, sym([0; 1]));
            testCase.verifyEqual(T2.C, sym([B/M, 0]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
            testCase.verifyEqual(eig(sys.A), eig(T2.A));
        end
        
        function testObservableCanonicalForm(testCase)
            % should convert state space to observable canonical form.
            sys = ctrldemo('massspring');
            
            T1 = canon(testCase.system1, 'o');
            T2 = canon(sys, 'o');
            
            testCase.verifyEqual(T1.A, sym([0, -2; 1, -3]));
            testCase.verifyEqual(T1.B, sym([3; 1]));
            testCase.verifyEqual(T1.C, sym([0, 1]));
            
            testCase.verifyEqual(T2.A, sym([0, -K/M; 1, -C/M]));
            testCase.verifyEqual(T2.B, sym([B/M; 0]));
            testCase.verifyEqual(T2.C, sym([0, 1]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
            testCase.verifyEqual(eig(sys.A), eig(T2.A));
        end
        
        function testJordanCanonicalForm(testCase)
            % should convert state space to Jordan canonical form.
            T1 = canon(testCase.system1, 'j');
            
            testCase.verifyEqual(T1.A, sym([-2, 0; 0, -1]));
            testCase.verifyEqual(T1.B, sym([2; -1]));
            testCase.verifyEqual(T1.C, sym([-1/2, -2]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
        end
        
        function testKalmanCanonicalForm(testCase)
            % should convert state space to Kalman canonical form.
            T1 = canon(testCase.system1, 'k');
            
            testCase.verifyEqual(T1.A, sym([-3, -2; 1, 0]));
            testCase.verifyEqual(T1.B, sym([1; 0]));
            testCase.verifyEqual(T1.C, sym([1, 3]));
            
            testCase.verifyEqual(eig(testCase.system1.A), eig(T1.A));
        end
    end
end

