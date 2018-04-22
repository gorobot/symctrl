function varargout = subvars(obj, varargin)
%SUBVARS Replaces variables with dummy variables for symbolic operations.

nout = nargout;

nx = cell(size(obj.states_));
nx(:) = {'SUBX'};

tx = sym(genvarname(nx, who));
varargout{1} = tx;

if nout > 1
    nu = cell(size(obj.inputs_));
    nu(:) = {'SUBU'};
    
    tu = sym(genvarname(nu, who));
    varargout{2} = tu;
end

if nout > 2
    varargout{3} = subs(obj.f, [obj.states; obj.inputs], [tx; tu]); 
end

if nout > 3
    varargout{4} = subs(obj.g, [obj.states; obj.inputs], [tx; tu]); 
end

end

