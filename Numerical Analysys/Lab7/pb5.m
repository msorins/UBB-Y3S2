f = @(x) 1 ./ (4 + sin(20 .* x));

a = 0;
b = pi;

ret = RepeatedSimpson(f, a, b, 30)