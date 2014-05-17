# Exercise 2: Make Is Your Python Now
## Extra Credit
### Create an all: ex1 target that will build ex1 with just the command make.
Now the Makefile looks like this:
```
CFLAGS = -Wall -g

all: ex1

clean:
	rm -rf ex1 ex1.dSYM
```
### Read man make to find out more information on how to run it.
We can use a file as a makefile.
```
$ cp Makefile myMakefile
$ make -f myMakefile clean
rm -rf ex1 ex1.dSYM
$ make -f myMakefile ex1
cc -Wall -g    ex1.c   -o ex1
```
