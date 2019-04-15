x = [0 10 20 30 40 60 80 100];
y = [0.0061 0.0123 0.0234 0.0424 0.0738 0.1992 0.4736 1.0133];


plot(x,y,'o');
hold on;

p = polyfit(x,y,2);
p2 = polyfit(x,y,3);
xTest = 0:0.1:100;
yRes = polyval(p,xTest);
yRes2 = polyval(p2,xTest);

yTest1 = polyval(p,[45]);
yTest2 = polyval(p2,[45]);
yGood = 0.0958;

format long;
fprintf('Approx at 45 2nd degree: %f\n', yTest1);
fprintf('Approx at 45 3rd degree: %f\n', yTest2); 
fprintf('Error at second degree %f\n', abs(yGood - yTest1));  
fprintf('Error at third degree degree %f\n', abs(yGood - yTest2));


plot(xTest, yRes);
plot(xTest, yRes2);
xlabel('Temperature');
ylabel('Presure');
legend('Points', '2degree', '3degree');
