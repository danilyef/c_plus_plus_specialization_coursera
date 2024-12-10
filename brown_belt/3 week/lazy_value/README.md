### Programming Task "LazyValue Template"

Sometimes, in practice, you encounter objects whose creation takes a significant amount of time, but they are not needed during every run of the program. For example, a version control system client may access local files or may need to access a remote repository. In this case, establishing a connection to the remote repository should only happen if the user decides to access it.

To represent such objects, a `LazyValue<T>` template can be useful. It has a constant method `const T& Get()`, which returns a reference to the created object. In its constructor, `LazyValue` accepts an initialization function, which is used during the first call to the `Get` method to create the stored object. Subsequent calls to `Get` simply return a reference to the stored object.

Thus, an object of class `LazyValue<T>` does not spend time creating the stored object until the first call to the `Get` method.

You are given the interface of the `LazyValue` template. Implement it. A more detailed list of requirements is as follows:

- An object of class `LazyValue<T>` should not construct an object of type `T` during its creation.
- During the first call to the `LazyValue<T>::Get` method, an object of type `T` should be created using the function passed to the `LazyValue<T>` constructor.
- Subsequent calls to the `Get` method should not invoke the function passed to the constructor.
- If during the lifetime of the `LazyValue<T>` object the `Get` method is never called, the initialization function should never be invoked.
- The `LazyValue` template should support working with types that do not have a default constructor.

The interface of the template is provided in the solution skeleton.