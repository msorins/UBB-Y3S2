function ExOne
x = [1 1.5 2 3 4];
f = [0 0.17609 0.30103 0.47712 0.60206];

plot(x, f, 'b--o')
hold on

% Compute the approximations
res = newtonInterpolation(x, f, 2.5)
plot(2.5, res, 'c*')
hold on

res = newtonInterpolation(x, f, 3.25)
plot(3.25, res, 'c*')
hold on

% Compute the error
err = 0
for i = 10:32
   err = max(err, abs( log( i / 10 ) - newtonInterpolation(x, f, i / 10)));
end
err

end
