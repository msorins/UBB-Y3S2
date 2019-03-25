function ret = newtonInterpolation(x, f, X)
    size(x,2)
    
    % Compute diff table
    diffTable = div_diff_table(x, f);
    
    ret = f(1);
    prod = 1;
    for i = 1:size(x, 2) - 1
        prod = prod * (X - x(i));
        ret = ret + prod * diffTable(i+2);
    end
end