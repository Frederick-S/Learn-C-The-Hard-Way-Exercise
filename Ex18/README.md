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
