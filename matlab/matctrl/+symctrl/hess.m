function H = hess(A)

n = size(A, 1);

A = symctrl.mat2se(A);

cptr = libpointer('stringPtrPtr', A);
resptr_H = libpointer('stringPtrPtr', A);

calllib('matctrl', ...
        'ml_linalg_hessenberg', ...
        n, ...
        cptr, ...
        resptr_H);

H = reshape(resptr_H.Value, n, n);

H = symctrl.se2mat(H);

clear('cptr');
clear('resptr_H');

end
