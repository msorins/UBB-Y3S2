function exThree

x = -1:0.01:3;

function ret = P(n, x)
  if (n == 0)
    ret = 1;
  else
    ret = P(n - 1, x) + x .^ n  / factorial(n);
  end
end

hold on;

leg = [];
for i = 0:6
  plot(x, P(i, x));
  leg = [leg; sprintf('P%d', i)];
end

legend(leg);
title('First 6 Taylor polynomials');

end