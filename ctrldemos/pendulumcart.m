%PENDULUMCART Summary of this function goes here

syms M m x(t) b l g theta(t) F I
f1 = (M + m)*diff(x, 2) + b*diff(x) + m*l*diff(theta, 2)*cos(theta) - m*l*diff(theta)^2*sin(theta) == F
f2 = (I + m*l^2)*diff(theta, 2) + m*g*l*sin(theta) == -m*l*diff(x, 2)*cos(theta)
