% Data
f = @(x) 2./(1+x.^2);
a = 0;
b  = 1;
q0 = (1/2)*(f(a) + f(b))

% Roomberk
syms j;
res = romberg(f,q0,1,a,b);
fprintf('romberg result is %.6f\n', res);

% Aitken
t0 = RepeatedTrapezium(f,a,b,1);
res2 = rombergAitken(f,2,t0,a,b);
fprintf('aitken result is %.6f\n', res2);