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
```

### There is a bug in this program because of strncpy being poorly designed. Go read about strncpy then try to find out what happens when the name or address you give is greater than 512 bytes. Fix this by simply forcing the last character to '\0' so that it's always set no matter what (which is what strncpy should do).
Create a python script to set long name:
```py
#!/usr/bin/env python

from subprocess import call

try:
    f = open('long-string.txt', 'r')
    name = f.read();
    arguments = ['./ex17', 'db.dat', 's', '1', name, 'zed@zedshaw.com'];
    
    call(arguments);
except Exception, e:
    print e
```

Set name that is greater than 512 bytes:
```
$ ./ex17 db.dat c
$ python set_long_name.py
$ ./ex17 db.dat l
1 abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrzed@zedshaw.com zed@zedshaw.com
```

Unexpected thing happened, the email address is appened to name.

Change the code to force the last character to '\0':
```c
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    
    if (addr->set) {
        die("Already set, delete it first");
    }
    
    addr->set = 1;
    
    // WARNING: bug, read the "How To Break It“ and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    addr->name[MAX_DATA - 1] = '\0';
    
    // demonstrate the strncpy bug
    if (!res) {
        die("Name copy failed");
    }
    
    res = strncpy(addr->email, email, MAX_DATA);
    addr->email[MAX_DATA - 1] = '\0';
    
    if (!res) {
        die("Email copy failed");
    }
}
```
```
$ ./ex17 db.dat c
$ python set_long_name.py
$ ./ex17 db.dat l
1 abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopq zed@zedshaw.com
```

### In the extra credit I have you augment the program to create arbitrary size databases. Try to see what the biggest database is before you cause the program to die for lack of memory from malloc.
It depends on the physical memory.

## Extra Credit
### The die function needs to be augmented to let you pass the conn variable so it can close it and clean up.
```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    
    Database_close(conn);
    
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    
    if (rc != 1) {
        die("Failed to load database.", conn);
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    
    if (!conn) {
        die("Memory error", conn);
    }
    
    conn->db = malloc(sizeof(struct Database));
    
    if (!conn->db) {
        die("Memory error", conn);
    }
    
    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        
        if (conn->file) {
            Database_load(conn);
        }
    }
    
    if (!conn->file) {
        die("Failed to open the file", conn);
    }
    
    return conn;
}

void Database_close(struct Connection *conn)
{
    if (conn) {
        if (conn->file) {
            fclose(conn->file);
        }
        
        if (conn->db) {
            free(conn->db);
        }
        
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);
    
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    
    if (rc != 1) {
        die("Failed to write database.", conn);
    }
    
    rc = fflush(conn->file);
    
    if (rc == -1) {
        die("Cannot flush database.", conn);
    }
}

void Database_create(struct Connection *conn)
{
    int i = 0;
    
    for (i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = { .id = i, .set = 0 };
        
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    
    if (addr->set) {
        die("Already set, delete it first", conn);
    }
    
    addr->set = 1;
    
    // WARNING: bug, read the "How To Break It“ and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    
    // demonstrate the strncpy bug
    if (!res) {
        die("Name copy failed", conn);
    }
    
    res = strncpy(addr->email, email, MAX_DATA);
    
    if (!res) {
        die("Email copy failed", conn);
    }
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = { .id = id, .set = 0 };
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;
    
    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];
        
        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        die("USAGE: ex17 <dbfile> <action> [action params]", NULL);
    }
    
    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;
    
    if (argc > 3) {
        id = atoi(argv[3]);
    }
    
    if (id >= MAX_ROWS) {
        die("There's not that many records", NULL);
    }
    
    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;
        case 'g':
            if (argc != 4) {
                die("Need an id to get", NULL);
            }
            
            Database_get(conn, id);
            break;
        case 's':
            if (argc != 6) {
                die("Need id, name, email to set", NULL);
            }
            
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
        case 'd':
            if (argc != 4) {
                die("Need id to delete", NULL);
            }
            
            Database_delete(conn, id);
            Database_write(conn);
            break;
        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", NULL);
    }
    
    Database_close(conn);
    
    return 0;
}
```

### Change the code to accept parameters for MAX_DATA and MAX_ROWS, store them in the Database struct, and write that to the file, thus creating a database that can be arbitrarily sized.
[Reference](http://pastebin.com/MvLXkDCz).

### Add more operations you can do on the database, like find.
