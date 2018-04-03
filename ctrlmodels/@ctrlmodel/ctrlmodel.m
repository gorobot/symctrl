classdef (SupportExtensionMethods = true) ctrlmodel
    %CTRLMODEL Summary of this class goes here
    %   Detailed explanation goes here
    methods (Access = protected)
        function outputArg = method1(obj,inputArg)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            outputArg = obj.Property1 + inputArg;
        end
    end
end

