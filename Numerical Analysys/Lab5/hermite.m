function N = hermite(x, f, fDx,n, X)
  A = hermite_table(x,f,fDx,n);
  x = A(:,1)';
  
  A = A(1,2:end);
  ones(size(X'));
  cumprod(X' - x(1:end-1), 2);
  
  C = [ones(size(X')), cumprod(X' - x(1:end-1), 2)];

  N = A * C';

end