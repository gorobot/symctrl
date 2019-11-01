classdef (SupportExtensionMethods = true, InferiorClasses = {?sym}) randomvar < handle
    %RANDOMVAR Symbolic random variable.

    properties (Access = {?statespace, ?randomvar}, Hidden)
        % C Pointer Handle
        cobj_;

        % C Pointer Handle for Distribution
        dobj_;
    end

    properties
        distribution_name
    end

    methods
        function obj = randomvar(name, d, varargin)
            validateattributes(name, {'char'}, {'nonempty'});
            validateattributes(d, {'randomdistribution'}, {'nonempty'});
            validateattributes(varargin, {'cell'}, {'nonempty'});

            if ~isvarname(name)
                error('SYMCTRL::InvalidVariable', 'Invalid variable name.');
            end

            c = symctrl.mat2se(name);
            cptr = libpointer('stringPtrPtr', c);

            obj.dobj_ = calllib('matctrl', 'ml_random_number_distribution_new');

            switch d
                case randomdistribution.UniformInt
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_uniform_int_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.UniformReal
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_uniform_real_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                % case randomdistribution.Binomial
                %     validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                %     calllib('matctrl', ...
                %         'ml_binomial_distribution_set', ...
                %         obj.dobj_, ...
                %         varargin{1});

                case randomdistribution.NegativeBinomial
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_negative_binomial_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Geometric
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_geometric_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Poisson
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_poisson_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Exponential
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_exponential_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Gamma
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_gamma_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Weibull
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_weibull_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.ExtremeValue
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_extreme_value_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Normal
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_normal_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Lognormal
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_lognormal_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.ChiSquared
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_chi_squared_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Cauchy
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_cauchy_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.FisherF
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_fisher_f_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.StudentT
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_student_t_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                % case randomdistribution.Discrete
                %     obj.dobj_ = calllib('matctrl', ...
                %         'ml_discrete_distribution_set', ...
                %         varargin{:});
                %
                % case randomdistribution.PiecewiseConstant
                %     obj.dobj_ = calllib('matctrl', ...
                %         'ml_piecewise_constant_distribution_set', ...
                %         varargin{:});
                %
                % case randomdistribution.PiecewiseLinear
                %     obj.dobj_ = calllib('matctrl', ...
                %         'ml_piecewise_linear_distribution_set', ...
                %         varargin{:});

            end

            obj.cobj_ = calllib('matctrl', 'ml_random_variable_new', ...
                                cptr, ...
                                obj.dobj_);

            clear('cptr');
        end

        function delete(obj)
            calllib('matctrl', 'ml_random_number_distribution_free', obj.dobj_);
            calllib('matctrl', 'ml_random_variable_free', obj.cobj_);
        end
    end

    % Utility methods.
    methods (Hidden)
        function S = sym(obj)
            %SYM Helper function to allow functionality with sym class
            %functions.
            c = cell(1);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', 'ml_random_variable_name_get', ...
                    obj.cobj_, ...
                    cptr);

            S = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end
    end

    methods
        function r = sample(obj, gen)
            validateattributes(gen, {'randomdevice'}, {'nonempty'});

            r = calllib('matctrl', 'ml_random_variable_sample', ...
                        obj.cobj_, ...
                        gen.cobj_);
        end
    end

    % Overloaded operators.
    methods
        function C = plus(A, B)
            %PLUS Overloaded to allow symbolic manipulation.
            if isa(A, 'randomvar')
                C = A.sym()+B;
            else
                C = A+B.sym();
            end
        end

        function C = minus(A, B)
            %MINUS Overloaded to allow symbolic manipulation.
            if isa(A, 'randomvar')
                C = A.sym()-B;
            else
                C = A-B.sym();
            end
        end

        function C = uminus(A)
            %UMINUS Overloaded to allow symbolic manipulation.
            C = -A.sym();
        end

        function C = uplus(A)
            %UPLUS Overloaded to allow symbolic manipulation.
            C = A.sym();
        end

        function C = mtimes(A, B)
            %MTIMES Overloaded to allow symbolic manipulation.
            if isa(A, 'randomvar')
                C = A.sym()*B;
            else
                C = A*B.sym();
            end
        end

        function C = mrdivide(A, B)
            %MRDIVIDE Overloaded to allow symbolic manipulation.
            if isa(A, 'randomvar')
                C = A.sym()/B;
            else
                C = A/B.sym();
            end
        end

        function C = mpower(A, B)
            %MPOWER Overloaded to allow symbolic manipulation.
            if isa(A, 'randomvar')
                C = A.sym()^B;
            else
                C = A^B.sym();
            end
        end
    end
end
