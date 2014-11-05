# Exercise 16: Structs And Pointers To Them
## How To Break It
### Try passing NULL to Person_destroy to see what it does. If it doesn't abort then you must not have the -g option in your Makefile's CFLAGS.
```
$ ./ex16
Joe is at memory location 0x181e010:
Name: Joe Alex
        Age: 32
        Height: 64
        Weight: 140
Frank is at memory location 0x181e050:
Name: Frank Blank
        Age: 20
        Height: 72
        Weight: 180
Name: Joe Alex
        Age: 52
        Height: 62
        Weight: 180
Name: Frank Blank
        Age: 40
        Height: 72
        Weight: 200
ex16: ex16.c:28: Person_destroy: Assertion `who != ((void *)0)' failed.
Aborted (core dumped)
```

### Forget to call Person_destroy at the end, then run it under Valgrind to see it report that you forgot to free the memory. Figure out the options you need to pass to Valgrind to get it to print how you leaked this memory.
```
$ valgrind --leak-check=full ./ex16
==6098== Memcheck, a memory error detector
==6098== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==6098== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==6098== Command: ./ex16
==6098==
Joe is at memory location 0x51fa040:
Name: Joe Alex
        Age: 32
        Height: 64
        Weight: 140
Frank is at memory location 0x51fa0f0:
Name: Frank Blank
        Age: 20
        Height: 72
        Weight: 180
Name: Joe Alex
        Age: 52
        Height: 62
        Weight: 180
Name: Frank Blank
        Age: 40
        Height: 72
        Weight: 200
==6098==
==6098== HEAP SUMMARY:
==6098==     in use at exit: 69 bytes in 4 blocks
==6098==   total heap usage: 4 allocs, 0 frees, 69 bytes allocated
==6098==
==6098== 33 (24 direct, 9 indirect) bytes in 1 blocks are definitely lost in loss record 3 of 4
==6098==    at 0x4C2A45D: malloc (vg_replace_malloc.c:291)
==6098==    by 0x40067B: Person_create (ex16.c:15)
==6098==    by 0x4007B9: main (ex16.c:45)
==6098==
==6098== 36 (24 direct, 12 indirect) bytes in 1 blocks are definitely lost in loss record 4 of 4
==6098==    at 0x4C2A45D: malloc (vg_replace_malloc.c:291)
==6098==    by 0x40067B: Person_create (ex16.c:15)
==6098==    by 0x4007D6: main (ex16.c:46)
==6098==
==6098== LEAK SUMMARY:
==6098==    definitely lost: 48 bytes in 2 blocks
==6098==    indirectly lost: 21 bytes in 2 blocks
==6098==      possibly lost: 0 bytes in 0 blocks
==6098==    still reachable: 0 bytes in 0 blocks
==6098==         suppressed: 0 bytes in 0 blocks
==6098==
==6098== For counts of detected and suppressed errors, rerun with: -v
==6098== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 1 from 1)
```

### Forget to free who->name in Person_destroy and compare the output. Again, use the right options to see how Valgrind tells you exactly where you messed up.

```
$ valgrind --leak-check=full ./ex16
==6194== Memcheck, a memory error detector
==6194== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==6194== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==6194== Command: ./ex16
==6194==
Joe is at memory location 0x51fa040:
Name: Joe Alex
        Age: 32
        Height: 64
        Weight: 140
Frank is at memory location 0x51fa0f0:
Name: Frank Blank
        Age: 20
        Height: 72
        Weight: 180
Name: Joe Alex
        Age: 52
        Height: 62
        Weight: 180
Name: Frank Blank
        Age: 40
        Height: 72
        Weight: 200
==6194==
==6194== HEAP SUMMARY:
==6194==     in use at exit: 21 bytes in 2 blocks
==6194==   total heap usage: 4 allocs, 2 frees, 69 bytes allocated
==6194==
==6194== 9 bytes in 1 blocks are definitely lost in loss record 1 of 2
==6194==    at 0x4C2A45D: malloc (vg_replace_malloc.c:291)
==6194==    by 0x4EBD2B9: strdup (strdup.c:42)
==6194==    by 0x4006AB: Person_create (ex16.c:18)
==6194==    by 0x4007AA: main (ex16.c:44)
==6194==
==6194== 12 bytes in 1 blocks are definitely lost in loss record 2 of 2
==6194==    at 0x4C2A45D: malloc (vg_replace_malloc.c:291)
==6194==    by 0x4EBD2B9: strdup (strdup.c:42)
==6194==    by 0x4006AB: Person_create (ex16.c:18)
==6194==    by 0x4007C7: main (ex16.c:45)
==6194==
==6194== LEAK SUMMARY:
==6194==    definitely lost: 21 bytes in 2 blocks
==6194==    indirectly lost: 0 bytes in 0 blocks
==6194==      possibly lost: 0 bytes in 0 blocks
==6194==    still reachable: 0 bytes in 0 blocks
==6194==         suppressed: 0 bytes in 0 blocks
==6194==
==6194== For counts of detected and suppressed errors, rerun with: -v
==6194== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 1 from 1)
```

### This time, pass NULL to Person_print and see what Valgrind thinks of that.
```
$ valgrind ./ex16
==6260== Memcheck, a memory error detector
==6260== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==6260== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==6260== Command: ./ex16
==6260==
Joe is at memory location 0x51fa040:
Name: Joe Alex
        Age: 32
        Height: 64
        Weight: 140
Frank is at memory location 0x51fa0f0:
Name: Frank Blank
        Age: 20
        Height: 72
        Weight: 180
==6260== Invalid read of size 8
==6260==    at 0x400733: Person_print (ex16.c:36)
==6260==    by 0x400828: main (ex16.c:55)
==6260==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==6260==
==6260==
==6260== Process terminating with default action of signal 11 (SIGSEGV)
==6260==  Access not within mapped region at address 0x0
==6260==    at 0x400733: Person_print (ex16.c:36)
==6260==    by 0x400828: main (ex16.c:55)
==6260==  If you believe this happened as a result of a stack
==6260==  overflow in your program's main thread (unlikely but
==6260==  possible), you can try to increase the size of the
==6260==  main thread stack using the --main-stacksize= flag.
==6260==  The main thread stack size used in this run was 8388608.
==6260==
==6260== HEAP SUMMARY:
==6260==     in use at exit: 69 bytes in 4 blocks
==6260==   total heap usage: 4 allocs, 0 frees, 69 bytes allocated
==6260==
==6260== LEAK SUMMARY:
==6260==    definitely lost: 0 bytes in 0 blocks
==6260==    indirectly lost: 0 bytes in 0 blocks
==6260==      possibly lost: 0 bytes in 0 blocks
==6260==    still reachable: 69 bytes in 4 blocks
==6260==         suppressed: 0 bytes in 0 blocks
==6260== Rerun with --leak-check=full to see details of leaked memory
==6260==
==6260== For counts of detected and suppressed errors, rerun with: -v
==6260== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 1 from 1)
Segmentation fault (core dumped)
```

## Extra Credit
### How to create a struct on the stack, which means just like you've been making any other variable.
