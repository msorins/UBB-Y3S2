function ExTwo
x = [100 121 141];
f = [10 11 12];

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
Y = lagrange(x, f, 115)
hold on
plot(115, Y, 'c*')


end