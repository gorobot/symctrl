function G = symss2symtf(varargin)
%SYMSS2SYMTF Summary of this function goes here
%   Detailed explanation goes here

ni = nargin;

if ni == 1 && isa(varargin{1}, 'symss')
    sys = varargin{1};
    A = sys.A;
    B = sys.B;
    C = sys.C;
    D = sys.D;
    
elseif ni == 4
    A = varargin{1};
    B = varargin{2};
    C = varargin{3};
    D = varargin{4};
    
end

syms s
G = C/(s*eye(size(A)) - A)*B + D;
[n, d] = numden(G);

G = symtf(n, d);

end

