function [U, T] = schur(A)

A = symctrl.hess(A);

n = size(A, 1);

A = symctrl.mat2se(A);

cptr = libpointer('stringPtrPtr', A);

resptr_U = libpointer('stringPtrPtr', A);
resptr_T = libpointer('stringPtrPtr', A);

calllib('matctrl', ...
        'ml_linalg_schur', ...
        n, ...
        cptr, ...
        resptr_U, ...
        resptr_T);

U = reshape(resptr_U.Value, n, n);
T = reshape(resptr_T.Value, n, n);

U = symctrl.se2mat(U);
T = symctrl.se2mat(T);

clear('cptr');
clear('resptr_U');
clear('resptr_T');

end
