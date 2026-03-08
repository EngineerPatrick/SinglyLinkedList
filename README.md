
# Singly linked list

[![CI GitHub](https://github.com/EngineerPatrick/SinglyLinkedList/actions/workflows/CI.yml/badge.svg?branch=main)](https://github.com/EngineerPatrick/SinglyLinkedList/actions/workflows/CI.yml)

## Summary

  A singly linked list library in C with an iterator API, plus a CLI demo app.

  Clear separation of responsibilities and enforced information hiding. 

## Quick Start

```

  - make / make all        #Compiles
  - make sanitize          #Detects memory/UB bugs at runtime
  - make run               #Launches
  - make clean             #Deletes compiled files and docs

```

## Examples

```c

#include <stdlib.h>
#include "singly_linked_list.h"

int main(void) {

  /* Using list_create to create a list of 5 nodes, returns ERR_OK on success: */

  List* list_ptr = NULL;
  size_t list_size = 5;
  int error_code = 0;

  error_code = list_create(list_size, &list_ptr);

  if (error_code != ERR_OK) {
    exit(EXIT_FAILURE);
  }

  It* it_ptr = NULL;
  size_t position = 3;
  int node_data = 0;

  /* Then, using iterator_create to create an iterator, move it to position 3 and extract the node data. */
  /* From now on, if ERR_OK is not returned then list_delete is called before exiting the app to prevent memory leaks: */

  error_code = iterator_create(&it_ptr);

  if (error_code != ERR_OK) {
    list_delete(&list_ptr);
    exit(EXIT_FAILURE);
  }

  /* And the same goes for iterator_delete: */

  error_code = iterator_topos(list_ptr, it_ptr, position);

  if (error_code != ERR_OK) {
    list_delete(&list_ptr);
    iterator_delete(&it_ptr);
    exit(EXIT_FAILURE);
  }

  error_code = iterator_getdata(it_ptr, &node_data);

  if (error_code != ERR_OK) {
    list_delete(&list_ptr);
    iterator_delete(&it_ptr);
    exit(EXIT_FAILURE);
  }

  /* And finally, use list_insert to create a new node at position 5 and assign the previously extracted data to it: */

  position = 5;

  error code = list_insert(list_ptr, node_data, position);

  if (error_code != ERR_OK) {
    list_delete(&list_ptr);
    iterator_delete(&it_ptr);
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}


```

## Features

  - Architectural modularity, encapsulation and opaque structs (List and Iterator)
  - Robust input handling
  - Dynamic memory and aggressive cleanup paths against leaks
  - Defensive parameter validation
  - Centralized error codes (enum)
  - ASan/UBSan check in CI via GitHub Actions

## API guarantees

  - The caller of list_create and iterator_create has the ownership and is responsible for deallocation by calling list_delete and iterator_delete
  - Every function returns a different error code for each case
  - No function accepts NULL parameters, if passed then an error code is returned
  

  | Function            | Complexity |
  |---------------------|------------|
  | list_create         | O(n)       |
  | list_delete         | O(n)       |
  | list_insert         | O(n)       |
  | list_remove         | O(n)       |
  | iterator_topos      | O(n)       |
  | Any other           | O(1)       |

## Project layout

```

.
├─ include/                # Public API
│  └─ singly_linked_list.h
├─ src/                    # Logic implementation
│  └─ singly_linked_list.c
├─ apps/cli/
│  ├─ UI.c                 # CLI (main app)
│  ├─ UI_input.c           # Input handling
│  ├─ UI_input.h
│  ├─ UI_output_error.c    # Output errors from list module
│  └─ UI_output_error.h
├─ docs/                   # Doxygen
│  └─ Doxyfile
├─ .github/workflows/      # CI workflow
│  └─ CI.yml
├─ Makefile
└─ README.md

```

## Docs

README.md used as Doxygen main page (USE_MDFILE_AS_MAINPAGE = README.md)

```

  - make docs             #Generates Doxygen docs

```

## License

This project is licensed under the MIT License — see the `LICENSE` file for details.
