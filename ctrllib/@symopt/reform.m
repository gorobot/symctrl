function T = reform(opt, attributes)
%REFORM Reformulate an optimization problem.
%   Detailed explanation goes here

p = inputParser;
validateAttr = @(C) validateattributes(C, {'cell'}, {'nonempty'});
addRequired(p, 'opt');
addOptional(p, 'attributes', cell.empty, validateAttr);
parse(p, opt, attributes);

attributes = p.Results.attributes;

T = opt;

for k = 1:numel(attributes)
    switch attributes{k}
        case 'slack'
            eq = T.isinequality(T.st);
            
            ns = cell(nnz(eq), 1);
            ns(:) = {'s'};
            s = sym(genvarname(ns, [who; {'s'}]));
            
            ch = cell2sym({children(T.st(eq))});
            ch = ch(:, 1) - ch(:, 2);
            
            T.st(eq) = ch + s == 0;
            T.st = [T.st; s >= 0];
            T.vars = [T.vars, s.'];
            
        case 'epigraph'
            t = sym('t');
            
            T.st = [T.f - t <= 0; T.st];
            
            T.f = t;
            T.vars = t;
            
        % Attributes with arguments.
        case 'barrier'
            r = getarg(attributes, k);
            
            eq = T.isinequality(T.st);
            ch = cell2sym({children(T.st(eq))});
            ch = ch(:, 1) - ch(:, 2);
            
            phi = -(1/r)*log(-ch);
            
            T.f = T.f + phi.'*ones(size(phi));
            T.st = T.st(~eq);
    end
end

    function arg = getarg(attr, k)
        try
            arg = attr{k + 1};
            if ischar(arg)
                error(['Invalid argument to ''', attr{k}, '''.']);
            elseif ~isnumeric(arg)
                error(['Argument to ', attr{k}, ' must be numeric.']);
            elseif isempty(arg)
                error(['Argument to ', attr{k}, ' must not be empty.']);
            end
        catch ME
            if strcmp(ME.identifier, 'MATLAB:badsubscript')
                error(['Insufficient arguments to ''', attr{k}, '''.']);
            else
                rethrow(ME);
            end
        end
    end

end

