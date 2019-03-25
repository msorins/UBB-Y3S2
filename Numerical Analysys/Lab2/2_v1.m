T = @(n, t) cos(n * acos(t));
t = -1:0.01:1;

hold on;

plot(t, T(1, t));
plot(t, T(2, t));
plot(t, T(3, t));

