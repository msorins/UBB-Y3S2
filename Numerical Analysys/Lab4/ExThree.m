function ExTwo
x = 1:2:115;
y = sqrt(x);

x = [1 1.5 2 3 4];
y = [0 0.17609 0.30103 0.47712 0.60206];

% Plot initial data
plot(x, y, 'b--o')
hold on

[zzz, m] = size(x);
f = [y'];
X = 2.5;

for i = 1:m
  for j = 1:i
    zdet = det([f(j, j), x(j) - X; f(i, j), x(i) - X]);
    f(i, j+1) = 1 / (x(i) - x(j)) * zdet;
  end
end

f(m, m)

plot(X, f(m,m), 'c*')
hold on

end

