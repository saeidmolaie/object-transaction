# object-transaction

A small single‑header C++ utility that provides **RAII‑style object transactions**. It allows you to modify an object safely and automatically roll back changes unless explicitly committed. This pattern mirrors database transactions, but for in‑memory C++ objects.

---

## Features

* Creates a temporary copy of an object when a transaction begins.
* If the transaction is committed, the temporary copy is discarded.
* If not committed by destruction time, the original object is restored using the copy.
* Ensures exception‑safety through RAII.
* Non‑copyable, non-movable.
* Header‑only.

---

## How It Works

When you construct `object_transaction<T>`, it stores a pointer to your original object and makes a deep copy of it. Any changes you make to the original object during the transaction remain tentative.

* Calling `commit()` marks the transaction as successful and deletes the copy.
* If `rollback()` is called, or if the object goes out of scope without commit, the original object is restored from the copy.

By default, the destructor calls `commit()`, meaning changes persist unless you explicitly roll back.

---

## Example Usage

```cpp
#include "object_transaction.hpp"
#include <iostream>

struct config
{
    int value;
};

int main()
{
    config cfg{10};

    {
        objtran::object_transaction<Config> tx(&cfg);

        cfg.value = 42; // tentative change

        // Uncomment to roll back
        // tx.rollback();

        // If left alone, destructor commits by default
    }

    std::cout << "Config value: " << cfg.value << "\n";
}
```

---
