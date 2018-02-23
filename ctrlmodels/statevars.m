function S = statevars(varargin)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

ni = nargin;
flags = {'real', 'clear', 'positive', 'rational', 'integer'};

if ni == 0
    w = evalin('caller', 'whos');
    allstatevars = {w(strcmp('statevar', {w.class})).name};
    if nargout == 1
%         S = cell2sym(allstatevars);
        S = allstatevars';
        return;
    end
    if numel(allstatevars) == 0
        return;
    end
    
    % Print the state variables defined in the caller.
    fprintf('\nYour state variables are:\n\n')
    for k = 1:numel(allstatevars)
        fprintf('    %s\n', allstatevars{k});
    end
    fprintf('\n');
    return;
end

if any(strcmp(varargin{end}, flags))
    control = varargin{end};
    args = varargin(1:end - 1);
else
    args = varargin;
end

% Define state variables.
for k = 1:numel(args)
    x = args{k};
    if isvarname(args{k}) && ~any(strcmp(x, flags))
        svarx = statevar(x);
        assignin('caller', x, svarx);
        
%         if ~isempty(control)
%             assume(svarx, control);
%         end
    % If a bracket occurs, this is a symbolic function.
    elseif ~isempty(find(x == '(', 1))
        [name, params] = symfun.parseString(x);
        svarx = statevar(symfun(x, [params{:}]));
%         svarx = statevar(x);
        assignin('caller', name, svarx);
    else
        error('Invalid state variable declaration.');
    end
end

end

