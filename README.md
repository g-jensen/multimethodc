# multimethodc

## Adds Clojure-like polymorphic dispatch to C in a single header file.

Just include `headers/multimethod.h` and it works!

### Example
![example.h.png](https://raw.githubusercontent.com/g-jensen/multimethodc/refs/heads/master/resources/example.h.png)
![example.c.png](https://raw.githubusercontent.com/g-jensen/multimethodc/refs/heads/master/resources/example.c.png)

The output of this program is:
```
Bark!
Meow!
Chirp!
Unknown Animal!
```

### Usage

multimethodc only supports functions with a single parameter.

- `defmulti(return_type, function_name, dispatch_type, param_type, param_name)` 
  - Put in header file to define a multimethod.
  - `return_type` return type of the multimethod
  - `function_name` name of the multimethod (used to call multimethod)
  - `dispatch_type` return type of the dispatch function (implemented with `implmulti`)
  - `param_type` type of the single parameter
  - `param_name` name of the single parameter

- `implmulti(return_type, function_name, default_value, dispatch_type, param_type, param_name)`
  - Put in source file dispatch function implementation (see example for syntax).
  - `default_value` is returned if no multimethod is found

- `implmulti_cmp(return_type, function_name, compare_fn, default_value, dispatch_type, param_type, param_name)`
  - same as `implmulti` but with a custom `compare_fn` that is used to compare the output of the dispatch function to each multimethod value. By default (like in `implmulti`), `==` is used to compare.

- `multimethod(return_type, function_name, value, param_type, param_name)`
  - implement a dispatch endpoint (see example for syntax).
  - this function is called if the dispatch function returns `value`.

- `free_multimethod(function_name)`
  - frees a multimethod. not super useful since you probably want a multimethod to exist for the entire runtime of the program.