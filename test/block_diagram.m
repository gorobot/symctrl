clear, clc, close all, reset(symengine)

D = ctrldemo('pendulum');

block(D.StateSpace)
