% Data
x = linspace(-5,5,15);
fx = arrayfun(@(t) sin(2*t), x);
fDx = arrayfun(@(t) 2*cos(2*t), x);
n = 15;

plot(x,fx);
hold on;

% For every point, compute and plot the estimation
testX = linspace(-5,5,100);
for i = testX
    res = hermite(x,fx,fDx,n, i);

    plot(i, res, 'c*')
    hold on
end




