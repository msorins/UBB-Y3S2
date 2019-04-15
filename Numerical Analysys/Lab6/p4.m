points = ginput(10)
x = points(:,1);
y = points(:,2);


plot(x,y, 'o');

hold on;

p = polyfit(x,y,2);
xTest = min(x):0.1:max(x);
yRes = polyval(p,xTest);

plot(xTest, yRes);

