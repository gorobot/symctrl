classdef (Abstract) ctrlmodel < handle & matlab.mixin.Copyable
    %CTRLMODEL Abstract superclass for system models.

    % Abstract methods.
    methods (Abstract)
        subs(obj)
        simplify(obj)
    end

    % % Protected Methods
    % methods (Access = protected)
    %     function T = copy(obj) {
    %         T = ctrlmodel;
    %
    %     }
    % end
end
