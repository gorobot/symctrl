function varargout = reduce(varargin)
%REDUCE Reduce a symbolic expression to a numeric expression.
%   
%   REDUCE(...) reduces a symbolic expression to a numeric expression using
%   VPA. 

varargout = cell(nargin);

for k = 1:nargin
    try
        varargout{k} = vpa(varargin{k});
    catch ME
        if strcmp(ME.identifier, 'something')
            varargout{k} = varargin{k};
        else
            rethrow(ME);
        end
    end
end

end

