for n = 10:15
    cnd = cond(hilb(n));
    fprintf('n = %d, cond(n) = %f\n', n, cnd);
end