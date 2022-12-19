#### Programming Task: Write a class declaration ####

You have been given the complete definition of the *Rectangle* class
```objectivec
class Rectangle {
public:
    Rectangle(int width, int height) : width_(width), height_(height)
    {
    }
    int GetArea() const {
        return width_ * height_;
    }
    int GetPerimeter() const {
        return 2 * (width_ + height_);
    }
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
private:
    int width_, height_;
};
```

Upload the *rectangle.h* header file containing the *Rectangle* class declaration. It should be a complete header file that can be used in a large project. In particular, the problem of double inclusion should be solved in it.