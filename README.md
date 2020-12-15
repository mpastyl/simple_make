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
If there are any circular dependencies it will detect them and abort.

It will also automatically replace $@, $< and $? with the appropriate variables.
