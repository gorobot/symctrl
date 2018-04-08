classdef roaTest < matlab.unittest.TestCase
    %ROATEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testRoaNonlinear1(testCase)
            % should return a region of attraction.
            sys = ctrldemo('vanderpol');
            R = roa(sys);
            testCase.verifyNotEqual(R, 0);
        end
        
        function testRoaNonlinear2(testCase)
            % should return a region of attraction.
            sys = ctrldemo('vanderpol2');
            R = roa(sys);
            testCase.verifyNotEqual(R, 0);
        end
        
        function testRoaGivenLyapunov(testCase)
            % should return a region of attraction.
            sys = ctrldemo('pendulum');
            syms(sys.states);
            V = x1^2/2 + x2^2/2;
            R = roa(sys, V);
            testCase.verifyNotEqual(R, 0);
        end
    end
end

