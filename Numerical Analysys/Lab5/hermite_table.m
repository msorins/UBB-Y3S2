function result = hermite_table(x, f1,fDx, n)
    m = n*2;
    result = zeros(m,m+1) * NaN;
    
    zIdx = reshape( cat( 1, 1:n, 1:n ), 1, [] );
    
    for i = 1:m
        result(i,1) = x(zIdx(i));
        result(i,2) = f1(zIdx(i));
    end
    
    for i = 1:m-1
        if mod(i, 2) == 1
            result(i,3) = fDx(idivide(i,int16(2)) + 1);
        else
            result(i,3)=(result(i+1,2)-result(i,2))/(result(i+1,1)-result(i,1));
        end
    end
    
    for j=4:m+1
        for i=1:m-j+2
            result(i,j)=(result(i+1,j-1)-result(i,j-1))/(result(i+j-2,1)-result(i,1));
        end
    end
    
    
end