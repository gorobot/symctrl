function M = ctrbs(A, B)

validateattributes(A, {'cell', 'char'}, {'nonempty'});
validateattributes(B, {'cell', 'char'}, {'nonempty'});

if ~iscell(A), A = {A}; end
if ~iscell(B), B = {B}; end

A = cellfun(@(x) {num2str(x)}, num2cell(A));
B = cellfun(@(x) {num2str(x)}, num2cell(B));

n = size(A, 2);
m = size(B, 2);

M = cell(1, n*n*m);

Aptr = libpointer('stringPtrPtr', A);
Bptr = libpointer('stringPtrPtr', B);
Mptr = libpointer('stringPtrPtr', M);

calllib('matctrl', 'ml_ctrbs', Aptr, Bptr, Mptr);

M = reshape(Mptr.Value, n, n*m);

clear('Mptr');

end
