classdef symtf < matlab.mixin.CustomDisplay
    %UNTITLED2 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        Numerator
        Denominator
    end
    
    properties (Access = protected, Dependent)
        tf
    end
    
    methods
        function obj = symtf(varargin)
            %SYMTF Symbolic transfer function.
            %   Detailed explanation goes here
            ni = nargin;
            
            if ni == 1
                switch class(varargin{1})
                    % If the arguments are another transfer function,
                    % create a new transfer function by copying all data. 
                    case 'symtf'
                        obj = varargin{1};
                        
                    % If the argument is a state space system, convert it
                    % to a transfer function using the C((sI-A)^-1)B + D
                    % equation. 
                    case 'symss'
                        obj = symss2symtf(varargin{1});
                        
                    % If we get a function instead, we need to convert it
                    % into a transfer function.
                    case 'symfun'
                        % Set initial conditions to zero.
                        
                    otherwise
                        error('Class is not supported.');
                end
            % If we get two parameters, we have a numerator and a
            % denominator. These could be arrays, corresponding to each
            % pair of a MIMO system.
            elseif ni == 2
                obj.Numerator = varargin{1};
                obj.Denominator = varargin{2};
            end
        end
        
        function Value = get.tf(obj)
            Value = obj.Numerator/obj.Denominator;
        end
    end
    
    methods (Access = protected)
        function header = getHeader(obj)
            if ~isscalar(obj)
                header = getHeader@matlab.mixin.CustomDisplay(obj);
            else
                headerStr = matlab.mixin.CustomDisplay.getClassNameForHeader(obj);
                headerStr = ['Symbolic transfer function ', headerStr, ' with properties:'];
                header = sprintf('%s\n',headerStr);
            end
        end
   
        function propgrp = getPropertyGroups(obj)
            if ~isscalar(obj)
                propgrp = getPropertyGroups@matlab.mixin.CustomDisplay(obj);
            else
                propList = struct('Numerator', obj.Numerator, ...
                                  'Denominator', obj.Denominator);
                
                propgrp = matlab.mixin.util.PropertyGroup(propList);
            end
        end
    end
end

