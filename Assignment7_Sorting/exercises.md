# Exercises

Discuss and answer the following questions (Please make sure to elaborate and justify your responses):

1. Explain what do you think the Big-Oh (worst-case) complexity of this algorithm is? Why?
2. What do you think the best-case complexity of this algorithm is?
   - Provide an example of an array of elements that fit the best-case.
3. Does insertion sort require any additional storage beyond the original array? Explain why or why not.
4. What is a 'stable sorting' algorithm? Is insertion sort a 'stable' algorithm, why or why not?

## Answers:

1. O(n^2). In worst case the data are sorted in reverse order, the total comparisons required are 1 + 2 + 3 + 4 + ... + (n-1) = (n-1)*n/2 = O(n^2), the total swaps needed are 1 + 2 + 3 + 4 + ... + (n-1) = (n-1)*n/2 = O(n^2) as well.
2. O(n). The best-case the data are sorted already in correct order, e.g.(sorted by ascending) 1, 2, 3, 4, 5, 6, ... , n. Then the total comparisons needed is 1 + 1 + 1 + ... + 1 = n = O(n), the total swaps needed are O(1);
3. No, it doesn't. Because indertion sort is in-place sorting, the algorithm updates input sequence only through replacement or swapping of elements, no additional arrays are created to temporarily store data.
4. Stable sorting algorithms maintain the relative order of records with equal keys (i.e. values). That is, a sorting algorithm is stable if whenever there are two records R and S with the same key and with R appearing before S in the original list, R will appear before S in the sorted list. Insertion sort is a stable algorithm, because if two elements with the same key, they will not swap after comparison, so the relative order remains.
