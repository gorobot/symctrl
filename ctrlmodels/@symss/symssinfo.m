function S = symssinfo(sys)
%SYMSSINFO State-space system information.

S = struct();

t = sym('t');
k = sym('k');

% Check for nonlinear. 
[A, B, C, D] = getabcd(sys);
if nnz(has([A, B; C, D], [sys.states; sys.inputs])) ~= 0
    S.Type = 'NL';
else
    S.Type = 'L';
end

% Check for discrete & time-varying.
for v = [k, t]
    for n = 1:numel(sys.f)
        F = getsymfuns(symfun(sys.f(n), v));
        if ~isempty(F)
            break;
        end
    end
    
    if ~isempty(F)
        break;
    end
end

if ismember(v, {k}) || ~isempty(sys.Ts)
    S.Type = ['D', S.Type];
end

if ~isempty(F)
    S.Type = [S.Type, 'TV'];
else
    S.Type = [S.Type, 'TI'];
end

end

