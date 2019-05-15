A = [400 -201; -800 401];
b = [200;200];

% a
res1 = A\b

% b
Aa = [401 -201; -800 401];
res2 = Aa\b

% c
condA = cond(A)