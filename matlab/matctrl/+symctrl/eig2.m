function L = eig2(A, tol)

n = size(A, 1);

A = symctrl.mat2se(A);

L = cell(1);

cptr = libpointer('stringPtrPtr', A);
resptr_L = libpointer('stringPtrPtr', L);

calllib('matctrl', ...
        'ml_linalg_first_eigenvalue', ...
        n, ...
        cptr, ...
        resptr_L, ...
        tol);

L = resptr_L.Value;

L = symctrl.se2mat(L);

clear('cptr');
clear('resptr_L');

end
