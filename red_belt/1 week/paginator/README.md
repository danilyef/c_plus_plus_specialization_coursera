#### Programming Task "Paginator Template" ####

Task:
In the lecture, we developed the Head function that allows iterating through the beginning of a container using a for loop. In this task, we will take a step forward and create a Paginator template that divides the content of the container into several pages. A classic example where this might be useful in practice is distributing a list of mobile applications across the screens of a phone. Suppose we have a vector of all applications on our phone, and on one screen, we can display 20 application icons. We can distribute the applications across screens with code like this:

```cpp
vector<vector<Application>> DistributeAmongScreens(const vector<Application>& apps) {
  vector<vector<Application>> result;
  for (const auto& page : Paginate(apps, 20)) {
    result.push_back({page.begin(), page.end()});
  }
  // result[0] - all applications that fit on the first screen,
  // result[1] - all applications that fit on the second screen, and so on.
  return result;
}
```

Notice that our code is concise and elegant. We didn't have to write separate code to handle the last screen, which may contain fewer than 20 applications.

Now, develop a class template Paginator with the following properties:

- It has one template parameter: the iterator type.
- The constructor of the Paginator<Iterator> class takes three parameters:
  - Iterator begin
  - Iterator end – the pair of iterators begin and end define the half-open interval [begin; end), which we will slice into pages.
  - size_t page_size – the size of one page.
- Objects of the Paginator<Iterator> class can be iterated using a range-based for loop.
- The Paginator<Iterator> class has a method size_t size() const, which returns the number of pages the passed container was divided into.
- The pages themselves should also support iteration using a range-based for loop and have a method size_t size() const, which returns the number of objects on that page.

Detailed examples of usage can be found in the unit tests in the solution template.

Additionally, develop a template function Paginate that takes a reference to a container and a page size, and returns an object of the Paginator<It> class:

```cpp
template <typename C> ??? Paginate(C& c, size_t page_size)
```