function varargout = subvars(obj, varargin)
%SUBVARS Replaces variables with dummy variables for symbolic operations.

nout = nargout;

nx = cell(size(obj.states));
nx(:) = {'SUBX'};

tx = sym(genvarname(nx, who));
varargout{1} = tx;

if nout > 1
    nu = cell(size(obj.inputs));
    nu(:) = {'SUBU'};

    tu = sym(genvarname(nu, who));
    varargout{2} = tu;
end

if nout > 2
    tf = cell([1, obj.nmodes]);

    for k = 1:obj.nmodes
        tf{k} = subs(obj.f(k), [obj.states; obj.inputs], [tx; tu]);
    end
    
    varargout{3} = tf;
end

if nout > 3
    varargout{4} = subs(obj.g, [obj.states; obj.inputs], [tx; tu]);
end

end

