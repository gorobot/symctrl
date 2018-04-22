function z = zero(sys)
%ZERO Computes the zeros of a system.

p = inputParser;
addRequired(p, 'sys', ...
    @(S) validateattributes(S, {'symss', 'symtf'}, {'nonempty'}));
parse(p, sys);

if isa(sys, 'symss')
    sys = symss2symtf(sys);
end

z = double(root(sys.Numerator));

end

