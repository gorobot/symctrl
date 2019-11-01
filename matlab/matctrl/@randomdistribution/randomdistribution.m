classdef randomdistribution
    % RANDOMDISTRIBUTION Enumeration class for random distributions.
    properties (GetAccess = {?randomvar}, Hidden)
        name_;
    end

    methods
        function obj = randomdistribution(name)
            obj.name_ = name;
        end
    end

    enumeration
        UniformInt              ('uniform_int_distribution')
        UniformReal             ('uniform_real_distribution')
        Binomial                ('binomial_distribution')
        NegativeBinomial        ('negative_binomial_distribution')
        Geometric               ('geometric_distribution')
        Poisson                 ('poisson_distribution')
        Exponential             ('exponential_distribution')
        Gamma                   ('gamma_distribution')
        Weibull                 ('weibull_distribution')
        ExtremeValue            ('extreme_value_distribution')
        Normal                  ('normal_distribution')
        Lognormal               ('lognormal_distribution')
        ChiSquared              ('chi_squared_distribution')
        Cauchy                  ('cauchy_distribution')
        FisherF                 ('fisher_f_distribution')
        StudentT                ('student_t_distribution')
    end
    % Discrete                ('discrete_distribution')
    % PiecewiseConstant       ('piecewise_constant_distribution')
    % PiecewiseLinear         ('piecewise_linear_distribution')
end
