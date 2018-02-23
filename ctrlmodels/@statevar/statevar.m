classdef (InferiorClasses={?sym}) statevar < sym
    %UNTITLED7 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Access = private)
        type_;
    end
    
    methods
        function obj = statevar(varargin)
            %STATEVAR Statevar constructor.
            
            privType = 'sym';
            
            if nargin ~= 0
                x = varargin{1};
                if isa(x, 'symfun')
                    privType = 'symfun';
                else
                    if ischar(x)
                        if ~isempty(find(x == '(', 1))
                            [~, params] = symfun.parseString(x);
                            xsym = symfun(x, [params{:}]);
                            varargin{1} = xsym;
                            % xsym = sym(x);
                            % varargin{1} = formula(xsym);
                            privType = 'symfun';
                        end
                    end
                end
            end
            
            % Superclass constructor.
            obj = obj@sym(varargin{:});
            
            % Internal variable type.
            obj.type_ = privType;
        end
    end
    
    % Concatenation methods.
    methods (Hidden = true)
        function obj = cat(dim, varargin)
        %CAT Statevar concatenation function.
            xsym = cat@sym(dim, varargin{:});
            obj = statevar(xsym);
            % obj = xsym;
        end

        function obj = horzcat(varargin)
            obj = cat(2, varargin{:});
        end
        
        function obj = vertcat(varargin)
            obj = cat(1, varargin{:});
        end
    end
    
    % Indexing methods.
    methods (Hidden = true)
        function varargout = subsref(obj, S)
            switch S(1).type
                case '()'
                    if strcmp(obj.type_, 'symfun')
                        if ~isempty(find(char(obj) == '(', 1))
                            % If the variable name has parentheses, we
                            % evaluate its parameters using
                            % symfun.parseString.
                            [~, params] = symfun.parseString(char(obj));
                        else
                            % Otherwise, we use all of the symbolic
                            % variables defined in the expression.
                            params = {symvar(obj)};
                        end
                        xsym = symfun(obj, [params{:}]);
                        varargout = {xsym(S.subs{:})};
                    else
                        varargout = {builtin('subsref', obj, S)};
                    end
                otherwise
                    varargout = {builtin('subsref', obj, S)};
            end
        end
    end
end

