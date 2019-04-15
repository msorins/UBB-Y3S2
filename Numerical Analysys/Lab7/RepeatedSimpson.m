function ret = RepeatedSimpson(f, a, b, n)
  samples = linspace(a, b, n + 1);
  temp = (samples(2:end) + samples(1:end-1))/2;
  ret = (b-a)/(6*n) * (f(a)+f(b) + 4*sum(arrayfun(f, temp))+ 2*sum(arrayfun(f, samples(2:end-1))));
end