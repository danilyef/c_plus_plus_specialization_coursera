#### Programming Task: "Cache"

In this task, we will work with `shared_ptr` in a multithreaded environment.

You will need to implement a cache for the backend of an e-library. There are many books stored on disk as archived text files. A user requests a book by its title. The book must be read, unpacked, and returned. Users often request the same books, so we want to cache them. At the same time, requests will come from multiple threads.

To access the books, we use the `ICache` interface, declared in the file `Common.h`. It has only one method, `GetBook()`, which returns a `shared_ptr` to a book (using the alias `BookPtr`). The implementation of this method should ensure correct caching.

A book is represented by the `IBook` interface. Its two methods, `GetName()` and `GetContent()`, allow you to get the book's title and its content, respectively.

Finally, reading and unpacking the book is done using the `IBooksUnpacker` interface. Its method `UnpackBook()` takes a book's title as input and returns the unpacked book as an `IBook` object.

To create an `ICache` object, a `MakeCache()` function needs to be implemented. This function accepts an `IBooksUnpacker` object and an `ICache::Settings` object containing cache settings. In this task, the settings include only one parameter, `max_memory` — the maximum total size of all cached books in bytes. In practice, there could be more settings, which is why they are defined as a structure. The size of a book is considered to be the size of its content in bytes.

The cache should operate based on the **Least Recently Used (LRU)** eviction method. Each cache entry has a rank. When the `GetBook()` method is called, if the book with the given title is already in the cache, its rank is updated to the highest value (strictly greater than all others). If the book is not in the cache, it is added to the cache, and its rank is again set to the highest value. If the total size of the books exceeds the `max_memory` limit, books with the lowest rank should be evicted from the cache as needed. It may even be necessary to clear the cache entirely. If the size of the requested book already exceeds the `max_memory` limit, the cache should remain empty after the method call, meaning the book is not added to the cache.

The `GetBook()` method can be called simultaneously from multiple threads, so thread safety must be ensured.

Practical implementations of LRU caches allow for finding entries by key and removing old entries in constant time. However, in this task, it is not required. You can search for the least recently used items by iterating through the existing ones.

In addition to `Common.h`, you are provided with two other files: `main.cpp` and `Solution.cpp`. The first contains a partial set of tests for the `MakeCache` function, and the second is a template for your solution. You need to implement the `MakeCache` function in `Solution.cpp` and submit this file to the testing system.