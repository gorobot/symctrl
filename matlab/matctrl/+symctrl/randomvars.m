function S = randomvars(varargin)

ni = nargin;
flags = {'uniform', 'bernoulli', 'binomial', 'geometric', 'poisson', ...
         'exponential', 'gamma', 'weibull', 'normal', 'lognormal', ...
         'chi_squared', 'cauchy', 'student'};

if ni == 0
    w = evalin('caller', 'whos');
    allrandomvars = {w(strcmp('randomvar', {w.class})).name};
    if nargout == 1
        S = allrandomvars.';
        return;
    end

    if numel(allrandomvars) ~= 0
        fprintf('\nRandom variables:\n\n')
         for k = 1:numel(allrandomvars)
             fprintf('    %s\n', allrandomvars{k});
         end
         fprintf('\n');
    end

    return;
end

if any(strcmp(varargin{end}, flags))
    dist = varargin{end};
    args = varargin(1:end - 1);
else
    args = varargin;
end

for k = 1:numel(args)
    x = args{k};
    if isvarname(args{k}) && ~any(strcmp(x, flags))
        rvarx = randomvar(x);
        assignin('caller', x, rvarx);

    elseif ~isempty(find(x == '(', 1))
        [name, params] = symfun.parseString(x);
        rvarx = statevar(symfun(x, [params{:}]));
        assignin('caller', name, rvarx);

    else
        error('SYMCTRL::InvalidVariable', 'Invalid variable name.');
    end
end

end
