# strlib

A from-scratch C++ string class built without relying on `std::string` internals, implementing manual memory management, the Rule of Five, operator overloading, and amortized capacity growth, with correctness verified using AddressSanitizer and UndefinedBehaviorSanitizer.

## Why this project

This is my first *real* C++ project, and my first time using git and GitHub. I wanted to get hands-on with pointers and manual memory management rather than just reading about them, and a string class felt like the right scope and small enough to actually finish, but big enough to force real decisions about ownership, allocation, lifetime and basic DSA knowledge.

The goal wasn't just "make it work" it was to build genuine intuition for pointers. That's why the core implementation (constructors, `operator+=`, growth logic) is deliberately written using raw pointer arithmetic (`*(ptr + i)`) instead of array-index syntax (`ptr[i]`), even though they compile to the same thing. Writing it the harder way, by hand, was the point. Once that intuition was built, later additions (planned algorithm functions) are expected to use `[]` — no need to keep proving the same thing twice. 

## What's implemented

- **Rule of Five** — constructor, destructor, copy constructor/assignment, move constructor/assignment
- **Operator overloading** — `==`, `!=`, `<`, `>`, `<=`, `>=`, `+`, `+=`, `[]` (const and non-const), stream insertion/extraction (`<<`, `>>`)
- **Amortized capacity growth** — `_length` (actual content) and `_capacity` (allocated space) are tracked separately, so repeated appends don't reallocate on every call
- **Element access** — `operator[]` (unchecked), `at()` (bounds-checked, throws `std::out_of_range`), `front()`, `back()`
- **Capacity management** — `reserve()`, `shrink_to_fit()`, `resize()` (with optional fill character)
- **Growth/mutation** — `push_back()`, `pop_back()`, `append()` (overloaded for `MyString`, `char`, and `const char*`), `clear()`
- **Iterators** — `begin()`/`end()` (const and non-const), enabling range-based `for` loops and STL algorithm compatibility (note : still missing full support but it is to be added)
- **Accessors** — `size()`, `length()`, `capacity()`, `empty()`, `c_str()`, `data()`

## What's not implemented yet

- `substr()`, `find()`, `insert()`, `erase()`, `replace()`
- `to_upper()` / `to_lower()`, `trim()`
- Small String Optimization (SSO) is considered after building all the foundation first. For now everything is heap allocated even for small strings at least once

## Design decisions worth explaining

### Manual loops over memcpy, and manual '\0' over strcpy

Operations like +=, append, substr, and insert copy characters with explicit for loops instead of memcpy/memmove, and set the null terminator by hand (buffer[length] = '\0';) instead of relying on strcpy. Writing the index math manually is what exposes bugs like wrong offsets, overlap hazards, off-by-one errors, and heap overflows from writing past an allocated buffer's bounds — the exact class of mistakes this project is meant to build intuition for. Since _length is tracked separately from buffer contents, placing '\0' explicitly keeps that invariant deliberate rather than implicit, which matters if embedded '\0' characters are ever supported, where _length would diverge from a strlen() scan.

### Capacity vs. length, and why `+=` doesn't reallocate on every call
Early versions of this class reallocated to the exact required size on every single `+=` call — correct, but O(n²) for repeated appends, since each append copied the entire string so far. The current design separates `_length` (characters in use) from `_capacity` (space actually allocated), and only reallocates when `_length` would exceed `_capacity` — giving amortized O(n) growth for building a string through repeated appends, matching the general strategy used by `std::vector` and `std::string` internally.

### Growth factor: 2x, matching GCC's `std::vector`, not MSVC's 1.5x — trade-off is fewer reallocations vs. worse memory reuse/fragmentation.

### `operator[]` vs. `at()`
`operator[]` performs no bounds checking (fast, matches `std::string`/`std::vector` convention for performance-critical access). `at()` explicitly checks bounds and throws `std::out_of_range` on failure. This mirrors the standard library's own split between the two, rather than picking one behavior for both.

### `reserve()` allocates exactly what's requested; internal growth doubles
`reserve(n)` guarantees capacity of at least exactly `n` — it does not apply the 2x growth multiplier. This is intentional: a user calling `reserve()` has already made an explicit sizing decision, and silently over-allocating beyond their request would be surprising. Internal automatic growth (via `push_back`/`+=`) doubles because it doesn't know if more appends are coming; `reserve()` does know, because the caller told it.

## Testing

There isn't a formal, automated test suite in the repo yet. The class has been manually exercised and debugged against a range of cases — Rule of Five behavior, self-assignment, self-move, capacity growth under repeated appends, and stream input edge cases — compiling and running with `-fsanitize=address,undefined` during development to catch memory errors.

```bash
g++ -std=c++17 -g -Wall -Wextra -fsanitize=address,undefined main.cpp -o main
```

## A note on commit history

The early commits on this repo bundle a lot of work together rather than reflecting granular, step-by-step progress — this project went through a lot of local iteration before being pushed for the first time. Going forward, commits will be smaller and more descriptive as new work (a real test, CI) gets added.

## Roadmap

- [ ] A real, automated test suite
- [ ] `substr()`, `find()`, `insert()`, `erase()`, `replace()`
- [ ] `to_upper()`, `to_lower()`, `trim()` & other relevant algorithmic functions
- [ ] CMake build setup
- [ ] GitHub Actions CI (build + test on every push)
- [ ] Possibly Implementing Small String Optimization


