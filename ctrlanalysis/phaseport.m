function phaseport(sv, varargin)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
% 
%   TODO:
%   - Add checking to ensure no symbolic variables are unset.
%   - Add capability to select which variables to analyze.
p = inputParser;

validateSys = @(sv) isa(sv, 'symsv');

addRequired(p, 'sv', validateSys);
addParameter(p, 'xlim', [-1:0.1:1]);
addParameter(p, 'ylim', [-1:0.1:1]);

parse(p, sv, varargin{:});

sv = p.Results.sv;

if ~ismember(symvar(rhs(sv.Dx)), lhs(sv.x))
    
end


l1 = p.Results.xlim;
l2 = p.Results.ylim;
[px1, px2] = meshgrid(l1, l2);

syms x1 x2
f = rhs(sv.Dx);
pDx1 = subs(f(1), [x1, x2], {px1, px2});
pDx2 = subs(f(2), [x1, x2], {px1, px2});

quiver(px1, px2, pDx1, pDx2)

end

