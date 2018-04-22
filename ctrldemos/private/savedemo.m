function savedemo(name, sys, varargin)
%SAVEDEMO Save system to file.
%   
%   SAVEDEMO(name, sys, C) saves the system defined by 'sys' and the
%   constants defined by 'C' to the filename defined by '<name>.mat'.

p = inputParser;
validateName = @(arg) ...
    validateattributes(arg, {'char', 'string'}, {'nonempty'});
addRequired(p, 'name', validateName);
addRequired(p, 'sys');
addOptional(p, 'C', cell.empty);
parse(p, name, sys, varargin{:});

C = {p.Results.C};

[folder, ~, ~] = fileparts(mfilename('fullpath'));
name = fullfile(folder, name);
save(name, 'sys', 'C');

end

