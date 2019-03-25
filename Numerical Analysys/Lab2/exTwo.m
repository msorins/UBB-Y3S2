function exTwo
    T = @(n, t) cos(n * acos(t));
    t = -1:0.01:1;
    hold on;

    for i = 1:4
        plot(t, P(i, t));
    end
end

function ret = P(n, x)
  if (n == 0)
    ret = 1;
  elseif(n == 1)
    ret = x;
  else
    ret = 2 .* x .* P(n - 1, x) - P(n - 2, x);
  end
end
