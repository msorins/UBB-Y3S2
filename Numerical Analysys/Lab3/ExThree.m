function ExThree
x = linspace(-3, 3, 21)
fun = @(x) (1 + cos(pi * x)) / (1 + x)
f = [];
for i = x
   j = i;
   f = [f, fun(j)];
end
f


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


plot(x, f, 'b--o')
X = -4:0.1:4;
for i = X
    j = i;
    Y = lagrange(x, f, j);
    hold on
    plot(j, Y, 'c')
end

end