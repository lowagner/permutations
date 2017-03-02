# permutations
small library for working with permutations

### Installation

#### Requirements
need the GNU MultiPrecision library for large number manipulation 
(e.g. getting the order of permutations, from 0 to N!-1).

    sudo apt-get install libgmp-dev

#### Make
just type `make`, and it should build the executable and test suite. 
run the program with `./main.perm` or the test suite with `./test.gperm`.

you can also create a debug executable with `make debug`.  this creates files with a `.g*` ending,
which can be debugged more easily with e.g. `gdb test.gperm` or `gdb main.gperm`.

executables without the `.g*` are optimized better.  note, however, that 
the test suite is automatically built for debugging, not speed.

### Tests
there is a test suite:  run `make test` and hope it successfully exits.

### License
distributed under the AGPL, read the `LICENSE`.
