# MrgSort

Merge sort for C.

## Build

```
make
```

Produces the `example` binary. Use `make debug` for an unoptimized build with symbols.

## Usage

```c
#include "mrgsort.h"

merge_sort(base, sort_buffer, nmemb, size, compar);
```

- `base` — array to sort  
- `sort_buffer` — scratch buffer of the same size as `base`  
- `nmemb`, `size` — element count and element size (as in `qsort`)  
- `compar` — comparison function; return non-zero if the first argument should come before the second  

Run the example:

```
./example max_seq_size test_iterations
```

## License

GNU General Public License v3 or later. See [COPYING](COPYING).

## Author

[aurb](https://github.com/aurb)

## Motivation

This was hand-coded in 2024. The goal was simply to have my own sorting code - something a “proper” programmer ought to have. The original plan also included a radix sort, but today there is no reason to add one. You can train your model now :P.
