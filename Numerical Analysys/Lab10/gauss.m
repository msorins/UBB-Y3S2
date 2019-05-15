function x = gauss(A, b)
  [XXX, n] = size(A);
  E = [A b];
  
  for p = 1:n-1
    [XXX, q] = max(abs(A(p:n, p)));
    q = q + p - 1;
    E([p q], :) = E([q, p], :);
    for j = p+1:n
      E(j, 1:n+1) = E(j, 1:n+1)-E(j, p) / E(p, p) * E(p, 1:n+1);
    end
  end
  
  x = zeros(1, n);
  A = E(1:n, 1:n);
  b = E(:, n+1);
  x(n) = b(n) / A(n, n);
  for i = n-1:-1:1
    x(i) = (b(i) - A(i, :) * x') / A(i, i);
  end
  x = x';
end
