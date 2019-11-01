classdef test_random_variable < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testRandomVarSampling(testCase)
            X = randomvar('X', randomdistribution.Normal, 5, 2);

            testCase.verifyEqual(X.sym(), sym('X'));

            gen = randomdevice();
            testCase.verifyTrue(isnumeric(X.sample(gen)));
        end

        function testRandomVarDistributions(testCase)
            % X = randomvar('X');

            gen = randomdevice();

            X = randomvar('X', randomdistribution.UniformInt, 1, 6);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.UniformReal, 1, 2);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            % X = randomvar('X', randomdistribution.Binomial, 4, 0.5);
            % testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.NegativeBinomial, 5, 0.75);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Geometric, 1, 0.5);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Poisson, 4);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Exponential, 1);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Gamma, 1, 1);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Weibull, 1, 1);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.ExtremeValue, 1, 0);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Normal, 5, 2);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Lognormal, 1.6, 0.25);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.ChiSquared, 1);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.Cauchy, 0, 1);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.FisherF, 1, 1);
            testCase.verifyTrue(isnumeric(X.sample(gen)));

            X = randomvar('X', randomdistribution.StudentT, 1);
            testCase.verifyTrue(isnumeric(X.sample(gen)));
        end
    end
end
