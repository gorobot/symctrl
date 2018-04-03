function z = zero(sys)
%ZERO Computes the zeros of a system.

p = inputParser;
validateSys = @(S) validateattributes(S, {'symss', 'symtf'}, {'nonempty'});
addRequired(p, 'sys', validateSys);
parse(p, sys);

if isa(sys, 'symss')
    sys = symss2symtf(sys);
end

z = double(root(sys.Numerator));

end

