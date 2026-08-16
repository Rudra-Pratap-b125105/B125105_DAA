USE OF LOOP INVARIANTS IN SORTING — SELECTION SORT

1. PSEUDOCODE — SELECTION SORT

SELECTION_SORT(A, n)

    for i ← 1 to n - 1 do

        min ← i

        for j ← i + 1 to n do
            if A[j] < A[min] then
                min ← j
            end if
        end for

        exchange A[i] and A[min]

    end for

    return A


2. WHAT IS A LOOP INVARIANT?

A loop invariant is a condition that remains TRUE before and after every
iteration of a loop. It is used to prove that an algorithm is correct.

For Selection Sort, the loop invariant is:

"At the beginning of iteration i, the elements A[1...i−1] are the
i−1 smallest elements of the array and are already in sorted order."

Example:

             Sorted              Unsorted
        +--------------+    +---------------+
        | 1  2  3 ...  |    | i ... n       |
        +--------------+    +---------------+
           A[1...i−1]           A[i...n]


THREE PARTS OF THE LOOP-INVARIANT PROOF

Initialization:
Before the first iteration, i = 1. The sorted portion A[1...0] is empty,
so the invariant is true.

Maintenance:
The algorithm finds the smallest element in A[i...n] and exchanges it
with A[i]. Therefore, A[1...i] is now sorted and contains the i smallest
elements.

Termination:
When the loop ends, A[1...n−1] contains the smallest n−1 elements in
sorted order. The last element must therefore be the largest, so the
entire array is sorted.


3. WHY DOES IT RUN FOR ONLY THE FIRST n−1 ELEMENTS?

The algorithm does not need to process the last element.

After the first n−1 positions have been correctly filled:

    [ smallest ... second largest | largest ]
                                     ↑
                               automatically correct

Only one element remains, and it must be the largest element.

Therefore:

    Outer loop runs n−1 times

Running it for n elements would perform an unnecessary final iteration.


4. WORST-CASE RUNNING TIME

The number of comparisons is:

    (n−1) + (n−2) + (n−3) + ... + 2 + 1

Using the sum:

    1 + 2 + ... + (n−1) = n(n−1)/2

Therefore:

    T(n) = Θ(n²)

Worst-case running time:

    Θ(n²)


5. BEST-CASE RUNNING TIME

Even if the array is already sorted, Selection Sort still searches the
entire unsorted portion to find the minimum.

For example:

    1 2 3 4 5

It still performs:

    4 + 3 + 2 + 1 = 10 comparisons

So the best case is not faster.

Best-case running time:

    Θ(n²)


FINAL ANSWER

Algorithm: Selection Sort

Loop invariant:
A[1...i−1] contains the i−1 smallest elements in sorted order.

Number of outer iterations:
n−1

Worst-case time:
Θ(n²)

Best-case time:
Θ(n²)

Is the best case better?
No.

Number of comparisons:
n(n−1)/2
