## Floating Point Benchmark for Automated Testing

This repository is a benchmark consisting of small foating point C/C++ programs to evaluate test generation methods.
It compiles 30 synthetic programs, pooled from [symex-fp-bench](https://github.com/delcypher/symex-fp-bench) from the [ASE17](https://srg.doc.ic.ac.uk/files/papers/klee-n-version-fp-ase-17.pdf) paper on floating point symbolic execution.

Each program in the benchmark comes in two versions, depending on how inputs are supplied.

- The first version (in `testcases`) is designed to be compiled as standalone binaries that read inputs from command line arguments.
The execution commands reside in the `harness` directory as python scripts.
This version is suitable for tools based on concrete executions, e.g., fuzzing. 

- The second version (in `testcases-klee`) is designed to run with KLEE, a state-of-the-art symbolic execution tool. 
When executed, these programs rely solely on `klee_make_symbolic` and take in no extra inputs/arguments.
