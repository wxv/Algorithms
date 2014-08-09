Multiplication Algorithms
=========================

Algorithms that multiply two numbers faster than long multiplication (`O(n^2)` time). These algorithms in particular are used in Python and GMP.

Algorithms
----------
**Karatsuba:** The first algorithm faster than the classical algorithm, reducing 4 mulitplications to 3. Calculates with multiplication of numbers about half the size along with addition, subtraction and shifting.

**Toom-Cook:** Method of multiplying by splitting up numbers into `k` parts (in this case, 3). In Toom-3 this reduces 9 multiplications to 5. The method used is described by Marco Bodrato. The digits are split and turned into 2 polynomials. Then the polynomials are evaluated at several points, the points are multiplied, and a new polynomial is interpolated based on an inverted matrix. Finally the result is recomposed from the new polynomial. Optimal matrices for `k` are described [here](http://www.csd.uwo.ca/~eschost/Exam/WhatAboutToomCookMatricesOptimality.pdf).





