% Data
f = @(x) 100/(x^2) * sin(10/x);
data = linspace(1,3,100);
eps = 10^(-4);

% Plot
a = 1;
b = 3;
y = arrayfun(f,data);
plot(data,y);

% Compute
approx = adaptiveQuad(f,a,b,eps);
fprintf('approx is %.6f', approx);