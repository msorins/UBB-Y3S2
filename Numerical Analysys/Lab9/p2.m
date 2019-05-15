A = [10 7 8 7; 7  5 6 5; 8 6 10 9; 7 5 9 10];
b = [32;23;33;31];


x1 = A\b
b2 = [32.1;22.9;33.1;30.9];

x2 = A\b2

condA = cond(A)


inputRelError = norm(b - b2) / norm (b)
outputRelError = norm(x1 - x2) / norm(x1)

totalRelError = outputRelError / inputRelError



A2 = [10 7 8.1 7.2; 7.08  5.04 6 5; 8 5.98 9.89 9; 6.99 4.99 9 9.98];
x3 = A2\b


inputRelError2 = norm(A - A2) / norm (A)
outputRelError2 = norm(x1 - x3) / norm(x1)

totalRelError2 = outputRelError2 / inputRelError2

