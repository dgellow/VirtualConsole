# Sam's Virtual 6502

## Tests

Tests files are located into `tests/CPU/`.

- One `.asm` file per group of instruction (load, store, branch, etc)
- A file `tests.cpp` in `CPU/src/` running the tests

### How to use them

You can use the bash script `run_tests.sh` at the root of the project to build the tests runner, asm files and run.

```
$ bash run_tests.sh cpu
```

### How to create new ones

If you want to create new tests, you have to make an asm file in `tests/CPU`. The filename should start with `tests_` and end with `.asm`. Then specify a new test in `CPU/src/tests.cpp`.
