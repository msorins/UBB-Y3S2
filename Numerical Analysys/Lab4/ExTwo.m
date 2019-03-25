function ExTwo
x = [1 1.5 2 3 4];
f = [0 0.17609 0.30103 0.47712 0.60206];

% Plot initial data
plot(x, f, 'b--o')
hold on

% Compute the approximations
res = newtonInterpolation(x, f, 2.5)
plot(2.5, res, 'c*')
hold on


% Plot interppolation data
X = -1:0.1:6;
for i = X
    j = i;
    Y = newtonInterpolation(x, f, j);

    plot(j, Y, 'c*')
    hold on
end

end

