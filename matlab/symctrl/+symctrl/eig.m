function [l, V] = eig(A)
    n = size(A, 1);

    A = cellfun(@(x) {num2str(x)}, num2cell(A));

    l = cell(1, n);

    cptr = libpointer('stringPtrPtr', A);

    resptr_l = libpointer('stringPtrPtr', l);
    resptr_V = libpointer('stringPtrPtr', A);

    calllib('matctrl', ...
            'ml_la_compute_eigenvalues', ...
            n, ...
            cptr, ...
            resptr_l, ...
            resptr_V);

    l = reshape(resptr_l.Value, 1, n);
    V = reshape(resptr_V.Value, n, n);

    clear('cptr');
    clear('resptr_l');
    clear('resptr_V');
end
