function p = pole(sys)
%POLE Computes the poles of a system.

p = inputParser;
addRequired(p, 'sys', ...
    @(S) validateattributes(S, {'symss', 'symtf'}, {'nonempty'}));
parse(p, sys);

if isa(sys, 'symss')
    sys = symss2symtf(sys);
end

p = double(root(sys.Denominator));

end

