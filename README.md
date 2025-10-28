# Matrix Library

A C library implementing fundamental matrix operations with comprehensive unit testing.

## Overview

This project provides a complete implementation of basic matrix operations in C, including creation, arithmetic operations, transformations, and advanced mathematical computations.

## Features

The library implements the following operations:

- **Matrix Creation & Cleanup**
  - `create_matrix` - Create a new matrix with specified dimensions
  - `remove_matrix` - Free matrix memory

- **Matrix Comparison**
  - `eq_matrix` - Compare two matrices for equality (precision up to 6 decimal places)

- **Arithmetic Operations**
  - `sum_matrix` - Add two matrices
  - `sub_matrix` - Subtract two matrices
  - `mult_number` - Multiply matrix by a scalar
  - `mult_matrix` - Multiply two matrices

- **Transformations**
  - `transpose` - Transpose a matrix

- **Advanced Operations**
  - `determinant` - Calculate matrix determinant
  - `calc_complements` - Calculate matrix of cofactors
  - `inverse_matrix` - Find inverse matrix

## Data Structure

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

## Return Codes

All operations (except matrix comparison) return a result code:
- `0` - OK
- `1` - Error, incorrect matrix
- `2` - Calculation error (incompatible matrix sizes, matrix for which calculations cannot be performed, etc.)

## Building

### Requirements
- GCC compiler
- Make
- Check library (for unit tests)
- lcov/genhtml (for coverage reports)

### Compilation

```bash
# Build the library
make

# Run tests
make test

# Generate coverage report
make gcov_report

# Clean build artifacts
make clean
```

The build will produce `matrix.a` static library.

## Testing

The project includes comprehensive unit tests using the Check framework, covering:
- Matrix creation with valid and invalid parameters
- All arithmetic operations
- Edge cases and error handling
- Memory management

Tests provide at least 80% code coverage for each function.

## Usage Example

```c
#include "matrix.h"

int main() {
    matrix_t A, B, result;

    // Create matrices
    create_matrix(3, 3, &A);
    create_matrix(3, 3, &B);

    // Fill matrices with values
    // ... (your code to fill matrices)

    // Perform operations
    sum_matrix(&A, &B, &result);

    // Clean up
    remove_matrix(&A);
    remove_matrix(&B);
    remove_matrix(&result);

    return 0;
}
```

## Project Structure

```
matrix/
├── src/
│   ├── matrix.h              # Header file with declarations
│   ├── create_matrix.c       # Matrix creation
│   ├── remove_matrix.c       # Memory cleanup
│   ├── eq_matrix.c           # Matrix comparison
│   ├── sum_matrix.c          # Addition
│   ├── sub_matrix.c          # Subtraction
│   ├── mult_number.c         # Scalar multiplication
│   ├── mult_matrix.c         # Matrix multiplication
│   ├── transpose.c           # Transposition
│   ├── determinant.c         # Determinant calculation
│   ├── calc_complements.c    # Cofactor matrix
│   ├── inverse_matrix.c      # Matrix inversion
│   ├── tests.c               # Unit tests
│   └── Makefile              # Build configuration
└── README.md
```

## Development

The code follows Google C++ Style Guide adapted for C and adheres to POSIX.1-2017 standard.

## License

This project is developed as an educational implementation of matrix operations.
