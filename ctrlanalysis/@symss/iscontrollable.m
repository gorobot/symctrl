function tf = iscontrollable(sys)
%ISCONTROLLABLE Uses the eigenvector test to determine if a system is
%controllable. It returns a logical 1 (true) if the system is controllable
%and a logical 0 (false) if it is not.

sys = symss(sys);
[A, B, ~, ~] = sys.getabcd();

n = length(A);
L = unique(eig(A));
r = zeros([1 numel(L)]);

for k = 1:numel(L)
    r(k) = rank([(L(k)*speye(n) - A), B]);
end

tf = ~any(r < n);

end

