### Programming Task: Implementing a `UniquePtr` Template

You are asked to implement a simplified version of the `unique_ptr<T>` class. The full specification for the standard `unique_ptr` can be found on [cppreference](https://en.cppreference.com/w/cpp/memory/unique_ptr). For this task, you do not need to handle array specialization or provide a custom deleter. Your class should be named `UniquePtr`. The class should have one template parameter `T`, which represents the type of the object that the pointer will manage.

You should implement the following functions in the class:

1. **Default Constructor**: Creates an empty smart pointer.
   
2. **Constructor with T***: Accepts a raw pointer of type `T*` and takes ownership of this dynamically allocated memory.
   
3. **Move Constructor**: Takes an rvalue reference to another `UniquePtr` and transfers ownership of the resource from the other `UniquePtr`.
   
4. **Assignment Operator with `nullptr`**: Accepts a `nullptr` (type: `nullptr_t`, defined in the header `<cstddef>`). As a result, the smart pointer should become empty.

5. **Move Assignment Operator**: Accepts an rvalue reference to another `UniquePtr` and transfers ownership of the resource.

6. **Destructor**: Destroys the object, ensuring that the resource is properly cleaned up if owned by the pointer.

7. **Dereference Operator `*`**: Returns a reference to the object of type `T` managed by the smart pointer.

8. **Arrow Operator `->`**: Returns a pointer to the object, allowing access to its members using the `->` syntax.

9. **Release Function**: A function `T* Release()` that relinquishes ownership of the object and returns the raw pointer that was managed by the smart pointer.

10. **Reset Function**: A function `void Reset(T* ptr)` that takes ownership of a new raw pointer `ptr`, releasing any previously owned object.

11. **Swap Function**: A function `void Swap(UniquePtr& other)` that swaps the contents of the current smart pointer with another `UniquePtr`.

12. **Get Function**: A function `T* Get() const` that returns the stored pointer.

### Additional Requirements:
- **Copy Constructor and Copy Assignment Operator should be deleted**: The class should prohibit copying, as a `UniquePtr` represents exclusive ownership of a resource.
- **Standard `unique_ptr` and `<memory>` header are not allowed**: You must implement the functionality without using the standard library's `unique_ptr` or the `<memory>` header.

This task involves manually implementing smart pointer features such as memory management and resource ownership transfer, while ensuring that memory leaks or double frees are avoided.