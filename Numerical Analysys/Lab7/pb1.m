% Define data
f = @(x) 2/(1+x^2);
samples = 0:0.01:1;
y = arrayfun(f, samples);

% a) Approximate the integral using trapezium formula
a = 0;
b = 1;
n = size(samples,2);

approx = RepeatedTrapezium(f, a, b, n - 1)
fprintf('integral approx:  %f\n', approx);
plot(samples, y);
hold on

% b) plot the graphs
plot([0, 1], [f(0), f(1)]);
ylim([0, 2]);

% c) simpson
approx_s = RepeatedSimpson(f, a, b, n - 1)