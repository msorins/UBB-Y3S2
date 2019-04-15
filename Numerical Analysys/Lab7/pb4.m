f = @(x) x .* log(x);
hold on;

a = 1;
b = 2;
h = (b - a) / 2;

ret = RepeatedTrapezium(f, a, b, 10)