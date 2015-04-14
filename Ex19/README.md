# Exercise 19: A Simple Object System
## Extra Credit
### Update the Makefile so that when you do make clean it will also remove the object.o file.
```
CFLAGS = -Wall -g

all: ex19

ex19: object.o

clean:
	rm -rf ex19 object.o
```
