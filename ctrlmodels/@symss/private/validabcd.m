function tf = validabcd(varargin)
%VALIDABCD Validates whether matrix dimensions agree for a state space
%model.
%   
%   Checks whether A is nxn, B is nxm, C is pxn, and D is pxm.    
if isa(varargin{1}, 'symss')
    sys = varargin{1};
    [A, B, C, D] = getabcd(sys);
else
    A = varargin{1};
    B = varargin{2};
    C = varargin{3};
    D = varargin{4};
end

% Validate matrices.
[nA, nA2] = size(A);
[nB, mB] = size(B);
[pC, nC] = size(C);
[pD, mD] = size(D);
if nA ~= nA2
    error('symss:stateMatrixDimensions',...
        'State matrix dimensions are incorrect. State matrix must be square.');
elseif nA ~= nB
    error('symss:inputMatrixDimensions',...
        'Input matrix dimensions do not match state matrix.');
elseif nA ~= nC
    error('symss:outputMatrixDimensions',...
        'Output matrix dimensions do not match state matrix.');
elseif pC ~= pD || mB ~= mD
    error('symss:feedforwardMatrixDimensions',...
        'Feed-forward matrix dimensions do not match input/output matrix.');
else
    tf = true;
end

end
