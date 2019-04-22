function ret = rombergAitken(f,i,prev,a,b) 
    current = linspace(0,0,i);
    current(1) = RepeatedTrapezium(f,a,b,i);
    for j = 2:i
        current(j) = (4^(-j) * prev(j-1) - current(j-1))/(4^(-j) -1); 
    end
    
    if(abs(current(i) - prev(i-1)) > 10^(-5))
        ret = rombergAitken(f,i+1,current,a,b);
    else
        ret = current(i);
    end
    
    
end