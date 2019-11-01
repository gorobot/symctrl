classdef costfunction < handle
    %COSTFUNCTION Cost function.

    properties (Access = protected, Hidden)
        % C Pointer Handle
        cobj_;
    end

    methods
        function obj = costfunction()
            obj.cobj_ = calllib('matctrl', 'ml_std_function_new');
            % calllib('matctrl', 'ml_random_device_init', obj.cobj_);
        end

        function delete(obj)
            calllib('matctrl', 'ml_std_function_free', obj.cobj_);
        end
    end
end
