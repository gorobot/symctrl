classdef (Abstract) ctrlmodel < handle
    %CTRLMODEL Abstract superclass for system models.
    
    % Abstract methods.
    methods (Abstract)
        subs(obj)
        simplify(obj)
    end
end

