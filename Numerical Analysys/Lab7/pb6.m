f = @(x) 2 ./ sqrt(pi) * exp(x) .^ (-1 * x .^ 2);
a = 0;
b = 0.5;

ret = RepeatedSimpson(f, a, b, 4)
ret = RepeatedSimpson(f, a, b, 10)
