% II 1
x = 0:0.1:1
e = exp(1)
f = e.^(10 .* x .* (x - 1));
polyval(f, x)

% II 2
p = [1, -5, -17, 21]
r = roots(p)

% III 1
x = 0:0.1:1
f = e .^ (10 .* x .* (x - 1) .* sin(12 .* pi .* x))
plot(x, f)

x = 0:0.1:1
e = exp(1)
f = (3 * e) .^ (5 .* x .* x - 1) .* cos(12 .* pi .* x)
plot(x, f)

% III 2
syms a b
t = 0:0.1:10 * pi
x(a,b) = (a + b) * cos(t) - b * cos( (a / b + 1) * t )
y(a,b) = (a + b) * sin(t) - b * sin( (a / b + 1) * t )
plot(x(1, 2), y(1, 2))

% III 3
syms x
fa(x) = cos(x)
fb(x) = sin(x)
fc(x) = cos(2*x)

ezplot(fa)
hold on
ezplot(fb)
hold on
ezplot(fc)

% III 4
x = 0:50
f = zeros(1, 51)
for i = 0:50
  if mod(i, 2) == 0
    val = i / 2
  else 
    val = i * 3 + 1
  end
  f(i + 1) = val
end
plot(x, f)

% III 5
g = 1 / 2
for i = 1:5 
    g = 1 + g
end

% III 6
[x,y] = meshgrid(-5:.1:5);
e = exp(1)
g = e .^ (-1 .* ( (x - 1 / 2) .^ 2 + (y - 1 / 2) .^ 2 ) )
mesh(x, y, g)