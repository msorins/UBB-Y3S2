function ExOne
x = [1930 1940 1950 1960 1970 1980];
f = [123203 131669 150697 179323 203212 226505];

function A = a(x)
   [zzz, n] = size(x);
   ret = [];
   for i = 1:n
     diff = x - x(i);
     prd = 1 / (prod(diff(1:i-1)) * prod(diff(i+1:end)));
     ret = [ret, prd];
   end
   A = ret;
 end
 
 function L = lagrange(x, y, X)
   A = a(x);
   
   diff = X - x;
   num = sum(A .* y ./ diff);
   denom = sum(A ./ diff);
   L = num / denom;
 end



plot(x, f, 'x')
X = 1900:1:2000;
for i = X
    j = i
    Y = lagrange(x, f, j)
    hold on
    plot(j, Y, 'c*')
end


end