# Style Guide for Symbolic Controls Toolbox (Matlab)

**#1 RULE: MAKE CODE READABLE**
This rule overrules any subsequent rule in the document. Readability is
subjective, but users should be able to follow the function's process easily.

## General

* Do **not** use any toolboxes other than the Symbolic Toolbox.
* Do **not** rewrite basic Matlab functionality.

## Code

* Use spaces and parentheses wherever necessary to improve readability.
* Use multiple lines for complex function calls.

* Use matrix operations instead of `for` loops wherever possible.

### Variables & Naming

* Use short, mathematically descriptive variable names wherever possible.
  > For example,
  >
  > * Use `V` for a Lyapunov function instead of `lyapunovFunction`.
  > * Use `u` instead of `input`.

* Use short, descriptive `lowercase` abbreviations for functions instead of
`camelCase`.
  > For example,
  >
  > * Use `care` instead of `continuousAlgebraicRiccatiEquation`.

* Use `Uppercase` for matrix variables.
  > For example,
  >
  > * Use `M` instead of `m`.

* Use `lowercase` for scalar variables.
  > For example,
  >
  > * Use `x1` instead of `X1`.

* Use `Uppercase` for structures.
  > For example,
  >
  > * Use `Solutions` instead of `solutions`.

* Use `camelCase` for longer variable names or to denote mathematical operators
such as derivatives.
  > For example,
  >
  > * Use `someVariable` instead of `somevariable`.
  > * Use `dV` instead of `DV` or `DiffV`.

* Use `CamelCase` for function name/value pairs.
  > For example,
  >
  > * Use `ComputationTime` instead of `computationtime`.

* Use pluralized variable names for lists.
  > For example,
  >
  > * Use `states` instead of `state`.

* Do **not** use keywords or function names as variables.
  > For example,
  >
  > * Use `a` instead of `alpha`.
  > * Use `rho` instead of `rank`.

* Do **not** use underscores in variable or function names.
  > For example,
  >
  > * Use `someVariable` instead of `some_variable`.

* Use `lowercase` for boolean `is*` functions.
  > For example,
  >
  > * Use `ishurwitz` instead of `isHurwitz`.

### Spacing

* Use spaces around addition and subtraction operators.
  > For example,
  >
  > * Use `A + B` instead of `A+B`.

* Do **not** use spaces around multiplication and division operators.
  > For example,
  >
  > * Use `A*B` instead of `A * B`.

* Use spaces after commas.
  > For example,
  >
  > * Use `work(A, B)` instead of `work(A,B)`.
  > * Use `[A, B]` instead of `[A,B]`.
  > * Use `U{1, 1}` instead of `U{1,1}`.

* Use commas or semicolons to separate elements of an array or cell.
  > For example,
  >
  > * Use `[A, B]` instead of `[A B]`.

* Use spaces around equality or inequality operators.
  > For example,
  >
  > * Use `A = B` instead of `A=B`.
  > * Use `A <= B` instead of `A<=B`.

### Comments & Documentation

* All user-facing functions should include help documentation.

* Use comments to explain complex function calls or complex mathematical operations.

* Use a `Methodology:` section in the help instead of explaining methodology in the comments.

* Use indents to align inline comments to code.
  > For example,
  >
  > * Use
  >   ```matlab
  >   while true
  >     % Break loop.
  >     break;
  >   end
  >   ```
  >   instead of
  >   ```matlab
  >   while true
  >   % Break loop.
  >     break;
  >   end
  >   ```

* Use a leading empty line in help documentation.
  > For example,
  >
  > * Use
  >   ```matlab
  >   function Y = work(X)
  >   %WORK Do work.
  >   %
  >   %   WORK does some work on X and returns Y.
  >   ```
  >   instead of
  >   ```matlab
  >   function Y = work(X)
  >   %WORK Do work.
  >   %   WORK does some work on X and returns Y.
  >   ```

### Other

* Do **not** use `i` or `j` for loop iterator variables. Prefer `k` or singular variable names.
  > For example,
  >
  > * Use `for k in 1:numel(items)` instead of `for i in 1:numel(items)`.
  > * Use `for item in items` instead of `for i in items`.

* Use `numel` instead of `length` or `size` for 1-D arrays.
  > For example,
  >
  > * Use `numel(M)` instead of `length(M)`.

* Use `size` instead of `length` for matrices and N-D arrays.
  > For example,
  >
  > * Use `size(M, 1)` instead of `length(M)`.

* Use `reshape` instead of `transpose` or `.'` for 1-D arrays (unless the shape of the array is known beforehand).
  > For example,
  >
  > * Use `reshape(M, [], 1)` instead of `M.'`.

* Use `...` to wrap lines longer than 80 characters. The total line length should be less than 80 characters, including the `...` operator.

* Do **not** use `...` to break up large arrays passed as parameters.
  > For example,
  >
  > * Use
  >   ```matlab
  >   work(parameter1, ...
  >        [parameter2, parameter3]);
  >   ```
  >   instead of
  >   ```matlab
  >   work(parameter1, [parameter2, ...
  >        parameter3]);
  >   ```
  > * Use
  >   ```matlab
  >   p = [parameter2, ...
  >        parameter3];
  >   work(parameter1, p);
  >   ```
  >   instead of
  >   ```matlab
  >   work(parameter1, [parameter2, ...
  >        parameter3]);
  >   ```

* Use spaces to align wrapped function calls to the opening parentheses.
  > For example,
  >
  > * Use
  >   ```matlab
  >   work(parameter1, parameter2, ...
  >        parameter3, parameter4);
  >   ```
  >   instead of
  >   ```matlab
  >   work(parameter1, parameter2, ...
  >     parameter3, parameter4);
  >   ```

* Know the difference between the matrix transpose operator `.'` and the matrix complex conjugate operator `'`.

## Functions

* Use `speye` instead of `eye` wherever possible.

### Parameter Checking

* Use `inputParser` for functions with optional parameters, name/value pairs, and variable arguments.
  > For example,
  >
  > * Use
  >   ```matlab
  >   function Y = work(X, varargin)
  >   p = inputParser;
  >   addRequired(p, 'X');
  >   addOptional(p, 'Z', []);
  >   parse(p, X, varargin{:});
  >   Z = p.Results.Z;
  >   ```
  >   instead of
  >   ```matlab
  >   function Y = work(X, varargin)
  >   if nargin == 2
  >     Z = varargin{1};
  >   else
  >     Z = [];
  >   end
  >   ```

* Use `validateattributes` whenever possible.
  > For example,
  >
  > * Use
  >   ```matlab
  >   function Y = work(X)
  >   p = inputParser;
  >   validateInput = @(M) validateattributes(M, {'sym'}, {'square'});
  >   addRequired(p, 'X', validateInput);
  >   parse(p, X);
  >   ```
  >   instead of
  >   ```matlab
  >   function Y = work(X)
  >   [m, n] = size(X);
  >   if m ~= n
  >     error('Matrix is not square.');
  >   end
  >   if ~isa(X, 'sym')
  >     error('Matrix is not symbolic.');
  >   end
  >   ```

* Use boolean parameters instead of `'on'` or `'off'`.
  > For example,
  >
  > * Use `work(X, 'DoWork', true)` instead of `work(X, 'DoWork', 'on')`.

## Classes

* Group class properties and methods by type.

* Use dependent properties

### Directory Structure

* Use class folders `@class` or namespace folders `+namespace` for functions that overload controls toolbox functions.
  > For example,
  >
  > * Use `ctrlanalysis/@symss/lyap` instead of `ctrlanalysis/lyap`.

- All private utility functions should be closest to their calling functions.

- All user-facing functions should perform parameter checking unless the function explicitly calls another function or sets of functions.

- Group functions by use, and separate class methods to the appropriate use folder.

## Tests

* Tests should use demo systems when available.
* Tests should exist for every function for at least 3 systems (if applicable).
