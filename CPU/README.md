# Sam's Virtual CPU

- Emulates a 6502
- No dependencies
- Requires C++17 to build from source

## Build

```
$ mkdir -p build && cd build
$ cmake .. && make
```

## Unit tests

Tests located at [tests/unit](tests/unit).

The test runner is built by CMake resulting in an executable that can be directly executed:

```
$ mkdir -p build && cd build
$ cmake .. && make
$ ./virtualcpu_unit_test # or via CTest: 'ctest -R unit_test -V'
```

## Functional tests

Resources for functional tests are located at [tests/functional](tests/functional).

The directory [testdata](tests/functional/testdata) contains a pair of source (`.asm`) and binary (`.out`) files for each group of instruction (load, store, branch, etc). Binary files are generated by the script [tests/functional/generate_testdata.sh](tests/functional/generate_testdata.sh) then added into git for portablity. The current reference assembler is [dasm](http://dasm-dillon.sourceforge.net/).

The test runner is built by CMake resulting in an executable that can be directly executed:

```
$ mkdir -p build && cd build
$ cmake .. && make
$ ./virtualcpu_function_test # or via CTest: 'ctest -R functional_test -V'
```
