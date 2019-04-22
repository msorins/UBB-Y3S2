function ret = RepeatedTrapezium(f, a, b, n)
    samples = linspace(a, b, n + 1);
    
    ret = (b-a)/(2*n) * (f(a)+f(b) + 2*sum(arrayfun(f, samples(2:end-1))));
end