A Simple Make
------------------------------------
A simple rule parser and dependency resolver, similar to what make would do.

Preliminary Instructions
----------------------------------
To Build:

```
make
```

To run:

```
./simple_make
```

It will read rules in  stdin until EOF, then will output the commands based on the order needed to resolve the first target. 

Limitations
------------------------------
Will auto replace $@ with target but no other automatic variables. Does not currently detect circular dependencies.
