//code from Mark Allen Weiss textbook
// Modified by: Shihab Islam
// this is nano added line
//  The program uses a diverse amount of sorting techniques to sort information from vectors to the comparator.
// you will find implementations of  insertion, Heap, Quicksort, and mergesort which have varying speeds to sort from 
// greatest to least or vice versa.

#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <iostream>
#include <vector>
#include <functional>
 using namespace std;

/**
 * Simple insertion sort.
 */
template <typename Comparable, typename Comparator>
void insertionSort(vector<Comparable>& a, Comparator less_than)
{
    for (int p = 1; p < a.size(); ++p)
    {
        Comparable tmp = std::move(a[p]);

        int j;
        for (j = p; j > 0 && less_than(tmp, a[j - 1]); --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
 // a is the vector that we are sorting
 // left is the starting index of the vector
 // right is the last index of the vector
 // less_than is the Comparator that we pass to the sorting method  to indicate how the vector  is sorted
template <typename Comparable, typename Comparator>
void insertionSort(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    for (int p = left + 1; p <= right; ++p)
    {
        Comparable tmp = std::move(a[p]);
        int j;

        for (j = p; j > left && less_than(tmp, a[j - 1]); --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 * a is the vector that is being sorted
 */
template <typename Comparable>
void shellsort(vector<Comparable>& a)
{
    for (int gap = a.size() / 2; gap > 0; gap /= 2)
        for (int i = gap; i < a.size(); ++i)
        {
            Comparable tmp = std::move(a[i]);
            int j = i;

            for (; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = std::move(a[j - gap]);
            a[j] = std::move(tmp);
        }
}


/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild(int i)
{
    return 2 * i + 1;
}



/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable, typename Comparator>
void percDown(vector<Comparable>& a, int i, int n, Comparator less_than)
{
    int child;
    Comparable tmp;

    for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && less_than(a[child], a[child + 1])) {
            ++child;
        }
        if (less_than(tmp, a[child])) {      //tmp < a[ child ]
            a[i] = std::move(a[child]);
        }
        else {
            break;
        }
    }
    a[i] = std::move(tmp);
}



/**
 * Standard heapsort.
 */
 // a is the vector that we are sorting
 // less_than is the Comparator that we pass to the sorting algorithm  to indicate how the vector is sorted
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable>& a, Comparator less_than)
{
    for (int i = a.size() / 2 - 1; i >= 0; --i)  /* buildHeap */
        percDown(a, i, a.size(), less_than);
    for (int j = a.size() - 1; j > 0; --j)
    {
        std::swap(a[0], a[j]);               /* deleteMax */
        percDown(a, 0, j, less_than);
    }
}



/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
 // a is  the vector that we are sorting, that holds Comparable items
 // tmpArray holds merged vector
 // leftPos is the first position in the array
 // rightPos is the first index of the second half of the array
 // rightEnd is the last element in  array
 // less_than is the Comparator that we pass to the sorting algorithm  to indicate how the vector is sorted
template <typename Comparable, typename Comparator>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray,
    int leftPos, int rightPos, int rightEnd, Comparator less_than)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;


    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (less_than(a[leftPos], a[rightPos]))
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);

    while (leftPos <= leftEnd)  
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd)  
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}



/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */

template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable>& a,
    vector<Comparable>& tmpArray, int left, int right, Comparator less_than)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center, less_than);
        mergeSort(a, tmpArray, center + 1, right, less_than);
        merge(a, tmpArray, left, center + 1, right, less_than);
    }
}

/**
 * Mergesort algorithm (driver).
 */
 // a is  the vector of Comparable items that we are sorting
 // less_than is the Comparator that we pass to the sorting algorithm  to indicate how the vector is sorted
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable>& a, Comparator less_than)
{
    vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1, less_than);
}



/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
  // a is the vector that we are searching through to find the median
 // left is the starting position of the vector
 // right is the last position of the vector
 // less_than is the Comparator that we pass to the sorting algorithm  to indicate how the vector is sorted
template <typename Comparable, typename Comparator>
const Comparable& median3(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    int center = (left + right) / 2;

    if (less_than(a[center], a[left]))
        std::swap(a[left], a[center]);
    if (less_than(a[right], a[left]))
        std::swap(a[left], a[right]);
    if (less_than(a[right], a[center]))
        std::swap(a[center], a[right]);


    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}


/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void quicksort(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    if (left + 10 <= right)
    {
        const Comparable& pivot = median3(a, left, right, less_than);

        // Begin partitioning
        int i = left, j = right - 1;
        for (; ; )
        {
            while (less_than(a[++i], pivot)) {}
            while (less_than(pivot, a[--j])) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  

        quicksort(a, left, i - 1, less_than);     // Sort small elements
        quicksort(a, i + 1, right, less_than);    // Sort large elements
    }
    else 
        insertionSort(a, left, right, less_than);
}

/**
 * Quicksort algorithm (driver).
 */
 // a is  the vector of Comparable items that we are sorting
 // less_than is the Comparator that we pass to the sorting algorithm  to indicate how the vector is sorted
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable>& a, Comparator less_than)
{
    quicksort(a, 0, a.size() - 1, less_than);
}
//This function will perform the quick sort algorithm by using the middle or first pivot
// depending on the pivot parameter that is passed to the function
// a is the vector that is being sorted
// left is the starting index of the vector
// right is the last index of the vector
// less_than is the Comparator that we pass to the sorting algorithm in order show  how the vector is sorted
template <typename Comparable, typename Comparator>
void quicksort(vector<Comparable>& a, int left, int right, Comparable& pivot, Comparator less_than)
{
    if (left + 10 <= right)
    {

        // Begin partitioning
        int i = left, j = right - 1;
        for (; ; )
        {
            while (less_than(a[++i], pivot)) {}
            while (less_than(pivot, a[--j])) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  // Restore pivot

        quicksort(a, left, i - 1, less_than);     // Sort small elements
        quicksort(a, i + 1, right, less_than);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right, less_than);
}


//This function will call our quicksort function, and initialize the middle value of the vector
//  as the pivot, and it passes the pivot to quicksort function
// a is the vector that we are sorting
// less_than is the Comparator that we pass to the sorting algorithm   to indicate how the vector is sorted
//   to indicate how the vetor should be sorted
//Middle Pivot Wrapper
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable>& a, Comparator less_than) {
    int middle = (a.size() / 2) + 1;
    Comparable& pivot = a[middle];  //middle value of the array
    quicksort(a, 0, a.size() - 1, pivot, less_than);

}

//This function will call our quicksort function, and initialize the first value of the vector
//  as the pivot, and it passes the pivot to quicksort function
// a is the vector that we are sorting
// less_than is the Comparator that we pass to the sorting algorithm   to indicate how the vector is sorted
//First Pivot Wrapper
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable>& a, Comparator less_than) {
    Comparable& pivot = a[0];
    quicksort(a, 0, a.size() - 1, pivot, less_than);

}



/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect(vector<Comparable>& a, int left, int right, int k)
{
    if (left + 10 <= right)
    {
        const Comparable& pivot = median3(a, left, right);

        int i = left, j = right - 1;
        for (; ; )
        {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  

            
        if (k <= i)
            quickSelect(a, left, i - 1, k);
        else if (k > i + 1)
            quickSelect(a, i + 1, right, k);
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect(vector<Comparable>& a, int k)
{
    quickSelect(a, 0, a.size() - 1, k);
}


// items is the vector of items athat we are sorting
// less_than is the Comparator that we pass to the sorting algorithm in order to indicate how the vector should be sorted
template <typename Comparable, typename Comparator>
void SORT(vector<Comparable>& items, Comparator less_than)
{
    if (items.size() > 1)
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;

        auto chosenItem = items[items.size() / 2];

        for (auto& i : items)
        {
            if (less_than(i, chosenItem))
                smaller.push_back(std::move(i));
            else if (less_than(chosenItem, i))
                larger.push_back(std::move(i));
            else
                same.push_back(std::move(i));
        }

        SORT(smaller, less_than);     // Recursive call!
        SORT(larger, less_than);      // Recursive call!

        std::move(begin(smaller), end(smaller), begin(items));
        std::move(begin(same), end(same), begin(items) + smaller.size());
        std::move(begin(larger), end(larger), end(items) - larger.size());

        /*
                items.clear( );
                items.insert( end( items ), begin( smaller ), end( smaller ) );
                items.insert( end( items ), begin( same ), end( same ) );
                items.insert( end( items ), begin( larger ), end( larger ) );
        */
    }
}


/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename RandomIterator, typename Comparator>
void insertionSort(const RandomIterator& begin,
    const RandomIterator& end,
    Comparator lessThan)
{
    if (begin == end)
        return;

    RandomIterator j;

    for (RandomIterator p = begin + 1; p != end; ++p)
    {
        auto tmp = std::move(*p);
        for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
            *j = std::move(*(j - 1));
        *j = std::move(tmp);
    }
}


/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
template <typename RandomIterator, typename Comparator>
void insertionSort(const RandomIterator& begin,
    const RandomIterator& end)
{
    insertionSort(begin, end, less<decltype(*begin)>{ });
}


#endif
