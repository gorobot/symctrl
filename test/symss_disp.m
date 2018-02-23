clear, clc, clear all

A = [0 -1 1; 1 -2 1; 0 1 -1];
B = [1 0; 1 1; 1 2];
C = [0 1 0];
D = [0 0];

sys = symss(A, B, C, D);

scom = '';
combined = [sys.A, sys.B; sys.C, sys.D];
sz1 = size(combined, 1);
sz2 = size(combined, 2);

n = length(sys.A);

maxlen = 0;
for a = 1:numel(combined)
    slen = strlength(char(combined(a)));
    if slen > maxlen
        maxlen = slen;
    end
end

for a = 1:sz1
    scom = strcat(scom, sprintf('\n['));
    for b = 1:sz2
        scom = strcat(scom, sprintf(' %*s', maxlen, combined(a, b)));
        if b == n
            scom = strcat(scom, sprintf(' |'));
        end
    end
    scom = strcat(scom, sprintf(' ]\n'));
    if a == n
        scom = strcat(scom, sprintf('\n[ -'), ...
            repmat('-', 1, sz2 + sz2*maxlen), ...
            sprintf(' ]'));
    end
end

fprintf('%s\n\n', scom)
% fspec = '[ ';
% for k = 1:size(sys.A, 2)
%     fspec = strcat(fspec, '%*s ');
% end
% fspec = strcat(fspec, '| ');
% for k = 1:size(sys.B, 2)
%     fspec = strcat(fspec, '%*s ');
% end
% fspec = strcat(fspec, ']\n');
% 
% fprintf(fspec, combined.')

% X = [1,2;2,4;5,6];
% Y = [1;3;4];
% fprintf('-%d: %d %d\n', [Y,X].')

% fspec = '| x%d | %s | %s || x%d | + | %s || u%d |';
% for k = 1:n
%     if k==floor(n/2) 
%         sp='=';
%     else
%         sp=' ';
%     end
%     fprintf([fspec, '\n'], k, sp, ...
%             char(sys.A(k,:)), k, char(sys.B(k,:)), k);
% end
