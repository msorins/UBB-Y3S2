function ret = romberg(f,qPrev, k, a,b)
    
    h = b-a;
    j = 1:1:2^(k-1);
    qCurrent = 0.5 * qPrev + h/(2^k) * sum(f(a+(2.*j-1)/(2^k)*h))

    if(abs(qCurrent - qPrev) > 10^(-5))
        ret = romberg(f,qCurrent,k+1,a,b);
    else
        ret = qCurrent;
    end

end