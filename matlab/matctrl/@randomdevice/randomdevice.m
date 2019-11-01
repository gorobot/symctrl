classdef randomdevice < handle
    %RANDOMVAR Symbolic random variable.

    properties (GetAccess = {?randomvar}, Hidden)
        % C Pointer Handle
        cobj_;
    end

    methods
        function obj = randomdevice()
            obj.cobj_ = calllib('matctrl', 'ml_random_device_new');
            calllib('matctrl', 'ml_random_device_init', obj.cobj_);
        end

        function delete(obj)
            calllib('matctrl', 'ml_random_device_free', obj.cobj_);
        end
    end
end
