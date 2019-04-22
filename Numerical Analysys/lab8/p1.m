
% Data
f = @(x) 1/sqrt(2.*pi) .* exp(-((x.^2)./2));
integral(f, -5,5)
data = linspace(-5,5,100);
y = arrayfun(f,data);

% Plot data
plot(data,y);
hold on;
rectangleQuad(f,-5,5)

tests = linspace(-5,5,50);
tests2 = linspace(-5,5,500);

res50 = repeatedRectangle(f,-5,5,tests);
res500 = repeatedRectangle(f,-5,5,tests2);
fprintf('50 samples: %.6f\n500 samples: %.6f', res50,res500);