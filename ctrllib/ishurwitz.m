function tf = ishurwitz(A)
%ISHURWITZ Returns logical 1 (true) if the matrix or transfer function is
%Hurwitz, or logical 0 (false) if it is not.
%   
%   tf = ISHURWITZ(A) tests for Hurwitz conditions on a symbolic matrix.

p = inputParser;
validateMatrix = @(M) validateattributes(M, {'sym', 'numeric'}, {'square'});
addRequired(p, 'A', validateMatrix);
parse(p, A);

rL = real(eig(A));

if isa(A, 'sym')
    tf = ~any(isAlways(rL >= 0));
else
    tf = ~any(rL >= 0);
end

% if isa(varargin{1}, 'symss')
%     sys = symss(varargin{1});
%     [A, ~, ~, ~] = getMatrices(sys);
%     tf = ~any(real(eig(A)) >= 0);
% elseif isa(varargin{1}, 'symtf')
%     p = pole(varargin{1});
%     tf = ~any(real(p) >= 0);
% else
%     if isa(varargin{1}, 'sym')
%         % Symbolic expression. Treat it like a transfer function.
%         p = poles(varargin{:});
%         tf = ~any(real(p) >= 0);
%     elseif ismatrix(varargin{1}) && issquare(varargin{1})
%         % Square matrix. 
%         tf = ~any(real(eig(varargin{1})) >= 0);
%     else
%         error('Invalid argument.');
%     end
% end
    
end

