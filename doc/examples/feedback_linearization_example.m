clear, clc
syms x1 x2 u a
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f(1) = a*sin(x2);
sys.f(2) = -x1^2 + u;
sys.g(1) = x2;

Nsys = normal(sys);

%%
clear, clc
syms x1 x2 x3 u
syms a b c k theta
sys = symss;
sys.states = [x1 x2 x3];
sys.inputs = u;
sys.f(1) = -a*x1 + u;
sys.f(2) = -b*x2 + k - c*x1*x3;
sys.f(3) = theta*x1*x2;
sys.g(1) = x3;

Nsys = normal(sys);

%%
clear, clc
syms x1 x2 u
syms epsilon
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f(1) = x2;
sys.f(2) = -x1 + epsilon*(1 - x1^2)*x2 + u;
% sys.g(1) = x1 + x2^2;
sys.g(1) = x1;

Nsys = normal(sys);

%%
clear, clc
syms x1 x2 x3 u
sys = symss;
sys.states = [x1 x2 x3];
sys.inputs = u;
sys.f(1) = -x1 + ((2 + x3^2)/(1 + x3^2))*u;
sys.f(2) = x3;
sys.f(3) = x1*x3 + u;
sys.g(1) = x2;

Nsys = normal(sys);

%%
clear, clc
syms x1 x2 u mu
sys = symss;
sys.states = [x1 x2];
sys.inputs = u;
sys.f(1) = x2 + (-x1 - x1*x2^2)*u;
sys.f(2) = -x1 - mu*x2*(1 - x1^2) + (-x2 + x1^2*x2)*u;
sys.g(1) = (x1^2 + x2^2)/2;

Nsys = normal(sys);

%%
clear, clc
syms x1 x2 x3 g k m lambda mu R u
sys = symss;
sys.states = [x1 x2 x3];
sys.inputs = u;
sys.f(1) = x2;
sys.f(2) = g - k*x2/m - lambda*mu*x3^2/(2*m*(1 + mu*x1)^2);
sys.f(3) = ((1 + mu*x1)/lambda)*((lambda*mu*x2)/(1 + mu*x1)^2 - R)*x3 + (u + u*mu*x1)/lambda;
sys.g(1) = x1;

Nsys = normal(sys);

%%
clear, clc
syms x1 x2 x3 u
sys = symss;
sys.states = [x1 x2 x3];
sys.inputs = u;
sys.f(1) = -x1 + exp(2*x2)*u;
sys.f(2) = 2*x1*x2 + sin(x2) + u/2;
sys.f(3) = 2*x2;
sys.g(1) = x3;

Nsys = normal(sys);
