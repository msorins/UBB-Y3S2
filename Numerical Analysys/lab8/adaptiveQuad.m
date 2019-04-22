function ret = adaptiveQuad(f,a,b,err)
    i1 = simpson(f,a,b);
    i2 = simpson(f,a,(a+b)/2) + simpson(f,(a+b)/2,b);
    if(abs(i1-i2) < 15 *err)
        ret = i2;
    else
        ret = adaptiveQuad(f,a,(a+b)/2,err/2) + adaptiveQuad(f,(a+b)/2,b,err/2);
    end
    
end