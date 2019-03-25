eq1 = @(x) x;
eq2 = @(x) 3 / 2 .* x .^ 2 - 1 / 2;
eq3 = @(x) 5 / 2 .* x .^ 3 - 3 / 2 .* x;
eq4 = @(x) 35 / 8 .* x .^ 4 - 15 /4 .* x .^ 2 + 3 / 8;

x = 0:0.01:1;

subplot(1, 4, 1);
plot(x, eq1(x))

subplot(1, 4, 2);
plot(x, eq2(x))

subplot(1, 4, 3);
plot(x, eq3(x))

subplot(1, 4, 4);
plot(x, eq4(x))
