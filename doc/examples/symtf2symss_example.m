clear, clc

syms s a b c d
tf1 = 1/((s + a)*(s + b));
tf2 = 1/((s + a)*(s + c));
tf3 = 1/((s + b)*(s + d));
tf4 = 1/((s + c)*(s + d));
G = symtf([tf1, tf3; tf2, tf4])

%%
sys = symtf2symss(G)

%%
clear, clc
sys = ctrldemo('pendulum4');
Csys = canon(sys, 'j');

G1 = symss2symtf(Csys);

%%
sys2 = symtf2symss(G1);
Csys2 = canon(sys2, 'j');

G2 = symss2symtf(Csys2);
