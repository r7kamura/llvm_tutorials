# LLVM tutorials
LLVM tutorials for beginners.


## Environments
These contents are tested under following environments:

* Mac OSX 10.7
* LLVM 3.2 (installed via homebrew)
* Apple clang version 2.1


## Contents

### hello_world
The most basic example of LLVM assembly code.

```
$ cd hello_world
$ llvm-gcc -S -o hello_world.s
$ lli hello_world.s
Hello, world!
```


### handwritten_assembly_code
A tutorial for how to handwrite LLVM assembly code.

```
$ cd handwritten_assembly_code
$ lli handwritten_assembly_code.s
Hello, world!
```


### main_maker
A tutorial to create LLVM assembly code via C++ API of LLVM.

```
$ cd main_maker
$ clang++ -g main_maker.cpp -o main_maker.out `llvm-config --cppflags --ldflags --libs` -ldl -lpthread
$ ./main_maker.out 2>&1 | lli
Hello, world!
```
