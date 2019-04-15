%Data
x = [1 2];
fx = [0 0.6931];
fDx = [1 0.5];
xTest = 1.5;

h00 = @(t) (1+2*t)*(1-t)^2;
h10 = @(t) t*(1-t)^2;
h01 = @(t) t^2*(3-2*t);
h11 = @(t) t^2*(t-1);

xScaled = @(X) (X - x(1))/(x(2) - x(1));

p = @(t) h00(t)*fx(1) + h10(t)*(x(2)-x(1))*fDx(1) + h01(t)*fx(2) + h11(t)*(x(2)-x(1))*fDx(2);

res = p(xScaled(xTest))

error = abs(res - log(1.5))