function dV = lyapdiff(sys, V)
%LYAPDIFF Differentiate a given Lyapunov equation.

[tx, tu, tf] = subvars(sys);
Vs = subs(V, [sys.states; sys.inputs], [tx; tu]);
dV = gradient(Vs, tx).'*reshape(tf, [], 1);
dV = subs(dV, [tx; tu], [sys.states; sys.inputs]);

end
