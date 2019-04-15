% Data
r = 110;
p = 75;
H = @(x) 60 * r / (r ^ 2 - p ^ 2) * ((1 - (p / r) ^ 2 .* sin(x))) .^ 0.5
hold on;

% Params
a = 0;
b = 2 * pi;
h = (b - a) / 2;
n = 10

% Approximate
ret = RepeatedTrapezium(H, a, b, n)