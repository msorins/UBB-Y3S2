f = @(x,y) log(x+2*y);

a = 1.4;
b = 2;
c = 1;
d = 1.5;

approx = TrapeziumDouble(f, a, b, c, d)