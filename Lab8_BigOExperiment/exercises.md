Please edit this document below with your responses. Each question is worth 1/8 of your lab.

# Exercise 1

1. Record here how long it took you to run bubblesort and csort (Note: If you want to run several trials, say '10' and take an average that is an even better result!).

Bubblesort(3 trials average):               
real	0m0.422s                              
user	0m0.406s                              
sys	0m0.005s    
  
csort(3 trials average):  
real	0m0.017s  
user	0m0.004s  
sys	0m0.003s  

# Exercise 2

What is the Big-O complexity of bubblesort?

1. worst-case: O(n^2), average-case: O(n^2)

# Exercise 3

Do a little research and discover what algorithm qsort is in the C standard library. What is the algorithm? https://en.wikipedia.org/wiki/Qsort

1. qsort implements a polymorphic sorting algorithm for arrays of arbitrary objects according to a user-provided comparison function. It is named after the "quicker sort" algorithm, which was originally used to implement it in the Unix C library, although the C standard does not require it to implement quicksort.

# Exercise 4

What is the Big-O complexity of 'qsort' that we use in the csort program?

1. worst-case: O(n^2), average-case: O(nlog2n)

# Exercise 5

Is qsort's Big-O complexity better or worse than bubblesort? (Anser: Yes it is better/ No it is worse/ It is equal)

1. Yes, it is better

# Exercise 6

List the following functions in terms of their Big-O complexity from **smallest** to **largest**.
<img src="./media/bigo.jpg"/>

1. logN > N > N^2 > N^3 > 2^N > N!

# Exercise 7

- Given: f(n) = 3n^3 + n^2 + 27
- What is the O(n) of f(n)?

1. O(n^3)

# Exercise 8

- Given: f(n) = 3n^3 + n^2 + 27
- What are two constants c and k that prove your answer in exercise 7.
- when c = 31, for all n >= 1, |f(n)| <= c*|g(n)| holds.
