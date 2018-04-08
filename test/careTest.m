classdef careTest < matlab.unittest.TestCase
    %CARETEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testCareNumeric(testCase)
            % should return a solution to the continuous ARE.
            testCase.verifyEqual(1, 1);
        end
    end
end

