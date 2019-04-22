function ret = repeatedRectangle(f, a, b,x)
    n = size(x,2);
    ret = (b-a)/n* sum(arrayfun(f,x));
end