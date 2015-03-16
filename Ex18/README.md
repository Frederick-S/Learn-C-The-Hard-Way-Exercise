# Exercise 18: Pointers To Functions
## Extra Credit
### Get a hex editor and open up `ex18`, then find this sequence of hex digits that start a function to see if you can find the function in the raw program.
Yes, I find it.

### Find other random things in your hex editor and change them. Rerun your program and see what happens. Changing strings you find are the easiest things to change.
It displays `Segmentation faule (core dumped)`.

### Pass in the wrong function for the `compare_cb` and see what the C compiler complains about.
I passed a `do_nothing` function for `compare_cb`:

```c
void do_nothing()
{
}
```

```
$ make ex18
cc -Wall -g    ex18.c   -o ex18
ex18.c: In function ‘main’:
ex18.c:115:5: warning: passing argument 3 of ‘test_sorting’ from incompatible pointer type [enabled by default]
     test_sorting(numbers, count, do_nothing);
     ^
ex18.c:75:6: note: expected ‘compare_cb’ but argument is of type ‘void (*)()’
 void test_sorting(int *numbers, int count, compare_cb cmp)
```

### Pass in NULL and watch your program seriously bite it. Then run Valgrind and see what that reports.
Run the program:
```
$ ./ex18 4 1 7 3 2 0 8
0 1 2 3 4 7 8
8 7 4 3 2 1 0
3 4 2 7 1 0 8
Segmentation fault (core dumped)
```

The run with `Valgrind`:
```
$ valgrind ./ex18 4 1 7 3 2 0 8
==7958== Memcheck, a memory error detector
==7958== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==7958== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==7958== Command: ./ex18 4 1 7 3 2 0 8
==7958==
0 1 2 3 4 7 8
8 7 4 3 2 1 0
3 4 2 7 1 0 8
==7958== Jump to the invalid address stated on the next line
==7958==    at 0x0: ???
==7958==    by 0x4009B7: test_sorting (ex18.c:74)
==7958==    by 0x400B25: main (ex18.c:111)
==7958==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==7958==
==7958==
==7958== Process terminating with default action of signal 11 (SIGSEGV)
==7958==  Bad permissions for mapped region at address 0x0
==7958==    at 0x0: ???
==7958==    by 0x4009B7: test_sorting (ex18.c:74)
==7958==    by 0x400B25: main (ex18.c:111)
==7958==
==7958== HEAP SUMMARY:
==7958==     in use at exit: 56 bytes in 2 blocks
==7958==   total heap usage: 5 allocs, 3 frees, 140 bytes allocated
==7958==
==7958== LEAK SUMMARY:
==7958==    definitely lost: 0 bytes in 0 blocks
==7958==    indirectly lost: 0 bytes in 0 blocks
==7958==      possibly lost: 0 bytes in 0 blocks
==7958==    still reachable: 56 bytes in 2 blocks
==7958==         suppressed: 0 bytes in 0 blocks
==7958== Rerun with --leak-check=full to see details of leaked memory
==7958==
==7958== For counts of detected and suppressed errors, rerun with: -v
==7958== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
Segmentation fault (core dumped)
```

### Write another sorting algorithm, then change `test_sorting` so that it takes both an arbitrary sort function and the sort function's callback comparison. Use it to test both of your algorithms.
I added a quick sort function:
```py
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Our old friend die from ex17
void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    
    exit(1);
}

// A typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);

typedef int *(*custom_sort)(int *numbers, int count, compare_cb cmp);

// A classic bubble sort function that uses the
// compare_cb to do the sorting
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));
    
    if (!target) {
        die("Memory error.");
    }
    
    memcpy(target, numbers, count * sizeof(int));
    
    for (i = 0; i < count; i++) {
        for (j = 0; j < count - 1; j++) {
            if (cmp(target[j], target[j + 1]) > 0) {
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }
    
    return target;
}

void quick_sort_internal(int *target, int low, int high, compare_cb cmp);
int quick_sort_partition(int *target, int low, int high, compare_cb cmp);

int *quick_sort(int *numbers, int count, compare_cb cmp)
{
    int *target = malloc(count * sizeof(int));
    
    if (!target) {
        die("Memory error.");
    }
    
    memcpy(target, numbers, count * sizeof(int));
    
    quick_sort_internal(target, 0, count - 1, cmp);
    
    return target;
}

void quick_sort_internal(int *target, int low, int high, compare_cb cmp)
{
    if (low < high) {
        int pivot = quick_sort_partition(target, low, high, cmp);
        
        quick_sort_internal(target, low, pivot - 1, cmp);
        quick_sort_internal(target, pivot + 1, high, cmp);
    }
}

int quick_sort_partition(int *target, int low, int high, compare_cb cmp)
{
    int temp = 0;
    int pivot_value = target[(low + high) / 2];
    
    while (low < high) {
        while (cmp(target[low], pivot_value) < 0) {
            low++;
        }
        
        while (cmp(target[high], pivot_value) > 0) {
            high--;
        }
        
        if (low < high) {
            temp = target[low];
            target[low] = target[high];
            target[high] = temp;
        }
    }
    
    return high;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if (a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

// Used to test that we are sorting things correctly
// by doing the sort and printing it out.
void test_sorting(int *numbers, int count, compare_cb cmp, custom_sort sort)
{
    int i = 0;
    int *sorted = sort(numbers, count, cmp);
    
    if (!sorted) {
        die("Failed to sort as requested.");
    }
    
    for (i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    
    printf("\n");
    
    free(sorted);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        die("USAGE: ex18 4 3 1 5 6");
    }
    
    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;
    
    int *numbers = malloc(count * sizeof(int));
    if (!numbers) {
        die("Memory error.");
    }
    
    for (i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }
    
    printf("Bubble sort:\n");
    
    test_sorting(numbers, count, sorted_order, bubble_sort);
    test_sorting(numbers, count, reverse_order, bubble_sort);
    test_sorting(numbers, count, strange_order, bubble_sort);
    
    printf("Quick sort:\n");
    test_sorting(numbers, count, sorted_order, quick_sort);
    test_sorting(numbers, count, reverse_order, quick_sort);
    test_sorting(numbers, count, strange_order, quick_sort);
    
    free(numbers);
    
    return 0;
}
```

Run test:
```
$ ./ex18 4 3 7 11 13 23 37
Bubble sort:
3 4 7 11 13 23 37
37 23 13 11 7 4 3
4 3 7 11 13 23 37
Quick sort:
3 4 7 11 13 23 37
37 23 13 11 7 4 3
11 4 13 7 23 3 37
```

For quick sort, some input data may cause infinite loop because of `strange_order`, for example, `./ex18 1 2`.
