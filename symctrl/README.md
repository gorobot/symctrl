# Control Models

This folder contains the C++ classes describing the control models used in the library.

The two primary classes are `StateSpace` and `TransferFunction`.

## State Space

    dx/dt = Ax + Bu
        y = Cx + Du

The `StateSpace` model class contains four properties:

- `states`
- `inputs`
- `f`
- `g`

This model uses the notation `dx/dt = f(t, x, u)`.

To define a state equation, add an entry to the `f` vector.

## For Developers

### Lessons Learned

#### CMake

Sometimes, CMake will compile the library, but there are still linking errors in the C++ source that need to be resolved. `ldd` doesn't give complete error descriptions, so use `ld` instead.

```shell
> (cd build && cmake .. && make && make install)
> ld <path/to/library.so>
```
