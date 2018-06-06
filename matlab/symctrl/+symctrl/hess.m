function H = hess(A)
    n = size(A, 1);

    A = cellfun(@(x) {num2str(x)}, num2cell(A));

    cptr = libpointer('stringPtrPtr', A);
    resptr_H = libpointer('stringPtrPtr', A);

    calllib('matctrl', ...
            'ml_la_compute_hessenberg', ...
            n, ...
            cptr, ...
            resptr_H);

    H = reshape(resptr_H.Value, n, n);

    clear('cptr');
    clear('resptr_H');
end
