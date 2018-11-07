# Linear Algebra Functions

Most matrix and linear algebra software uses BLAS/LAPACK for numerical matrix manipulations. Because numerical methods are antithetical to symbolic manipulation, certain functionality needs to be ported to allow for symbolic computation.

The functions provided in this directory are designed to be used with SymEngine types, and will not guarantee the same level of performance as BLAS/LAPACK simply due to the nature of the computations.

## Advantages of Symbolic Manipulation

* Symbolic variables.
* Arbitrary precision.

The major advantages of performing symbolic manipulations is that these methods produce results that can utilize symbolic variables, as well as results of arbitrary precision.

For symbolic variables, this means we can omit certain unknown values, and observe their effect on the result after the computation. It is better in all cases to substitute variables and constants for their numerical equivalents prior to all linear algebra subroutines, but it is not always possible to do so, such as when unknown or tunable parameters are present, for example.

In addition, because symbolic computations are not strictly limited by variable sizes and machine precision, the results can be computed to arbitrary length, and this computation is not directly tied to a particular computer architecture. This is advantageous for a number of reasons, including portability, exactness, and avoiding round-off errors.

## Implementation

The linear algebra subroutines given in this library focus primarily on the functions required to work with control systems, with a particular focus on the QR and Schur decompositions.

It is not expected that the code will be fully optimized, and future revisions of the code may deal with performance issues that arise, specifically when dealing with symbolic variables. 
