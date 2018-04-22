function tf = isobservable(sys)
%ISOBSERVABLE Uses the eigenvector test to determine if a system is
%observable. It returns a logical 1 (true) if the system is observable and
%a logical 0 (false) if it is not.

sys = symss(sys);
[A, ~, C] = sys.getabcd();

n = length(A);
L = unique(eig(A));
r = zeros([1 numel(L)]);

for k = 1:numel(L)
    r(k) = rank([(L(k)*speye(n) - A); C]);
end

tf = ~any(r < n);

end
