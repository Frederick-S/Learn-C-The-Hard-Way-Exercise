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
