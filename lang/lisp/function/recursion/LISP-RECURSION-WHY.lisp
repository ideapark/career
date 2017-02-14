Recursion plays a greater role in Lisp than in most other languages. There
seem to be three main reasons why:
==================================

1. Functional programming. Recursive algorithms are less likely to involve
   side-effects.

2. Recursive data structures. Lisp's implicit use of pointers makes it easy
   to have recursively defined data structures. The most common is the list:
   a list is either nil, or a cons whose cdr is a list.

3. Elegance. Lisp programmers care a great deal about the beauty of their
   programs, and recursive algorithms are often more elegant than their
   iterative counterparts.


To solve a problem using recursion, you have to do two things:
==============================================================

1. You have to show how to solve the problem in the general case by breaking
   it down into a finite number of similar, but smaller, problems.

2. You have to show how to solve the smallest version of the problem -- the
   base case -- by some finite number of operations.
