function [U, T] = schur(A)
    n = size(A, 1);

    A = cellfun(@(x) {num2str(x)}, num2cell(A));

    cptr = libpointer('stringPtrPtr', A);

    resptr_U = libpointer('stringPtrPtr', A);
    resptr_T = libpointer('stringPtrPtr', A);

    calllib('matctrl', ...
            'ml_la_compute_schur', ...
            n, ...
            cptr, ...
            resptr_U, ...
            resptr_T);

    U = reshape(resptr_U.Value, n, n);
    T = reshape(resptr_T.Value, n, n);

    clear('cptr');
    clear('resptr_U');
    clear('resptr_T');
end
