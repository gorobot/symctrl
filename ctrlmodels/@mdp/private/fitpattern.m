function M = fitpattern(sz, X, idx)
%FITPATTERN Fit pattern into shape.

xidx = cell(1, ndims(X));
nidx = cell(1, ndims(sz));

[xidx{:}] = ind2sub(size(X), idx);
[nidx{:}] = ind2sub(size(sz), find(isnan(X)));

n = ndims(sz);
r = num2cell([nidx{:}] - [xidx{:}]);

M = X;

for k = 1:numel(r)
    s = repmat({':'}, 1, n);
    s{k} = -r{k};
    
    M = circshift(M, s{k}, k);
    
    if s{k} > 0
        s{k} = 1:s{k};
%         R = M(s{:});
%         q = s;
%         q{k} = size(M, k):-1:size(M, k) - s{k} + 1;
%         M(q{:}) = M(q{:}) + sum(R, k);
        M(s{:}) = 0;
    elseif s{k} < 0
        q = s;
        q{k} = size(M, k):-1:size(M, k) + s{k} + 1;
%         R = M(q{:});
%         s{k} = -s{k};
%         M(s{:}) = M(s{:}) + sum(R, k);
        M(q{:}) = 0;
    end
end

end

