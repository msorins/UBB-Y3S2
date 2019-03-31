x = [0 3 5 8 13];
fx = [0 225 383 623 993];
fDx = [75 77 80 74 72];
n = 5;
test = 10;


dist = hermite(x,fx,fDx,n, test)
speed = (993 - dist) / (13-10)

