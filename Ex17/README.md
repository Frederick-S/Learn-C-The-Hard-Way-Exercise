# Exercise 17: Heap And Stack Memory Allocation
## How To Break It
### The classic way is to remove some of the safety checks such that you can pass in arbitrary data. For example, if you remove the check on line 160 that prevents you from passing in any record number.
Remove the check in `Database_get`:
```
$ ./ex17 db.dat c
$ ./ex17 db.dat s 1 zed zed@zedshaw.com
$ ./ex17 db.dat d 1
$ ./ex17 db.dat g 1
1 // Wrong, it should be "ERROR: ID is not set"
```

### You can also try corrupting the data file. Open it in any editor and change random bytes then close it.
```
$ ./ex17 db.dat c
$ ./ex17 db.dat s 1 zed zed@zedshaw.com
$ ./ex17 db.dat g 1
1 zed zed@zedshaw.com
```
After corrupting the data file:
```
$ ./ex17 db.dat g 1
ERROR: Failed to load database.
```

### You could also find ways to pass bad arguments to the program when it's run, such as getting the file and action backwards will make it create a file named after the action, then do an action based on the first character.
```
$ ./ex17 c db.dat
Failed to open the file: No such file or directory

### There is a bug in this program because of strncpy being poorly designed. Go read about strncpy then try to find out what happens when the name or address you give is greater than 512 bytes. Fix this by simply forcing the last character to '\0' so that it's always set no matter what (which is what strncpy should do).

```
