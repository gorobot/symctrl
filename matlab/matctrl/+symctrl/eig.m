function [l, V] = eig(A)

A = symctrl.hess(A);

n = size(A, 1);

A = symctrl.mat2se(A);

l = cell(1, n);

cptr = libpointer('stringPtrPtr', A);

resptr_l = libpointer('stringPtrPtr', l);
resptr_V = libpointer('stringPtrPtr', A);

calllib('matctrl', ...
        'ml_linalg_eigenvalues', ...
        n, ...
        cptr, ...
        resptr_l, ...
        resptr_V);

l = reshape(resptr_l.Value, 1, n);
V = reshape(resptr_V.Value, n, n);

l = symctrl.se2mat(l);
V = symctrl.se2mat(V);

clear('cptr');
clear('resptr_l');
clear('resptr_V');

end
