% Data
x = [1:1:7];
y = [13 15 20 14 15 13 10];

plot(x,y,'o');
hold on;

p = polyfit(x,y,1);
xTest = 0:0.1:10;
yRes = polyval(p,xTest);


plot(xTest, yRes);

xlabel('Time');
ylabel('Temperature');

