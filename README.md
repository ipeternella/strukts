<h1 align="center">Strukts!</h1>

<p align="left">
  <img alt="C" src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white"/>
  <img alt="C++" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
  <img alt="CMake" src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmakelogoColor=white">
</p>

<p align="center"><img src="docs/strukts.png"></p>

## Table of Contents

- [Strukts](#Strukts)
  - [Objective](#Objective)
  - [Requirements](#Requirements)
  - [Dependencies](#Dependencies)
- [Compiling Strukts](#Compiling-Strukts)
- [Compiling Tests](#Compiling-Tests)

## Strukts

### Objective

Strukts is a C library with a few useful data structures/algorithms that can be reused in other C projects. It's main distribution contains a static lib, `libstrukts.a`, that can be statically linked to other C projects like the GNU linker [ld](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html).

Finally, this project is a training ground for exercising some classical algorithms and data structures implementations.

### Requirements

In order to compile Strukts and its tests, it's necessary to have:

- C compiler such as `gcc`, `clang`, etc.
- CMake for building the projects
- C++ compiler such as `g++`, `clang`, etc. (tests only)

### Dependencies

Strukts depends on the following third-party libraries:

- `GoogleTest` library for tests
- `GoogleMock` library for tests

Don't worry: this repo's CMake file downloads, compiles and links these dependencies automatically when building the lib tests.

## Compiling Strukts

First, clone this repo and create a build folder inside the cloned repo folder:

```sh
make build && cd build
```

Then, compile the project with `CMake`:

```sh
cmake .. && make
```

After this, the compiled static library will be at `build/lib/libstrukts.a`. This file can be statically linked
to your C project. Moreover, in order to use Struks's functions definitions, the library headers can be found at the repo's [include](include/strukts) folder.

## Compiling Tests

First, clone this repo and create a build folder inside the cloned folder:

```sh
mkdir build && cd build
```

Then, build the project with `CMake` with the flag `-DWITH_TEST=ON` which will fetch/compile/link the projects dependencies such as the [GoogleTest/GoogleMock](https://github.com/google/googletest) and finally compile and run
the tests:

```sh
cmake -DWITH_TEST=ON .. && make test
```

The test binaries can be found at `build/bin/test` which can be used to rerun the tests if there are no code changes.

`PS`: When any piece of code changes, running the aforementioned command will compile and run the tests again without
downloading external dependencies (faster).
