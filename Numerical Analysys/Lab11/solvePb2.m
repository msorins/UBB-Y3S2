function ret = solvePb2(A, b, er)
  [n, n] = size(A);
  x = rand(n, 1);
  new_x = rand(n, 1);
  M = diag(diag(A));
  N = M - A;
  T = M \ N;
  c = M \ b;
  cnt = 0;
  while(norm(x - new_x) > er * (1 - norm(T)) / norm(T))
    x = new_x;
    new_x = T * x + c;
    cnt = cnt + 1;
  end
  cnt
  ret = x;
end