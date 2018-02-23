function B = isobservable(sys)
%ISOBSERVABLE Uses the eigenvector test to determine if a system is
%observable. It returns a logical 1 (true) if the system is observable and
%a logical 0 (false) if it is not.
n = length(sys.A);
B = true;
egv = eig(sys.A);
for k = 1:numel(egv)
    if rank([(egv(k)*eye(n) - sys.A); sys.C]) < n
        B = false;
        return
    end
end

end

