# Math Library

This miniature mathematical library implements the linear algebra functions
needed by the Symbolic Controls Library. It is a (mostly) header-only,
template-driven library in the style of
[blaze](https://bitbucket.org/blaze-lib/blaze) or
[armadillo](http://arma.sourceforge.net)
[(1)](https://conradsanderson.id.au/misc/sanderson_templates_lecture_uqcomp7305.pdf)
meant to be used for working with basic types and
[SymEngine](https://github.com/symengine/symengine)'s symbolic types.

## Why another math library?

SymEngine provides an API for working with symbolic variables held in matrix
format, but the interface can be... problematic. Introducing new matrix
functions requires a lot of hacking, and many of the already-implemented
algorithms utilize friend methods to work with the underlying private class
variables, which aren't easily accessible from external methods that aren't
friended.

Most of the available libraries like
[blaze](https://bitbucket.org/blaze-lib/blaze) and
[armadillo](http://arma.sourceforge.net) similarly can't be easily extended to
utilize the way SymEngine handles operations like addition and multiplication.

So, to implement the minimal amount of linear algebra functions necessary for
the Symbolic Controls Library, this miniature matrix library works with both
basic types and symbolic variables using templated classes and functions which
allow for a generalized framework that works for all types.

## What does this library do?

The main purpose of this library is to provide a consistent way to work with matrices across all variable types, but it is specifically designed to implement:

- Jacobian and Hessian computations.
- Upper Hessenberg transformations.
- Schur decompositions.
- Hamiltonian and symplectic matrix solvers for the Riccati equation.

## For Developers

The idea behind many of the operations is to use SFINAE and template specialization to simplify operations and utilize specialized algorithms while the generic case falls back to basic matrix operations.
