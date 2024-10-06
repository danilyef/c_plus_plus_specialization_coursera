#### Programming Task "Textures"

In the lectures, you have been introduced to the smart pointer `shared_ptr`, which provides shared ownership of an object. In this task, you need to implement classes for shapes that can be rendered on an image and that jointly own a given texture.

Among the files available to you, the one that will primarily interest you is `Common.h`. It contains the interface `IShape`, which describes a shape. There are two types of shapes: a rectangle and an ellipse. They are specified in the enumeration `ShapeType`. Your task is to implement the `MakeShape` function, which creates a shape of the specified type.

The `IShape` interface allows you to query and set a number of properties of the shape: position, size, and texture. It also allows you to clone the shape using the `Clone()` method. This is similar to selecting a shape in a graphics editor and pressing `Ctrl+C` and `Ctrl+V`. The idea is that the cloned shape uses the same texture as the original. This is convenient because, in general, a texture can take up a lot of memory. Of course, a new texture can be assigned to the cloned shape later on.

A texture object should be deleted when there are no longer any shapes that own that texture. This can happen when a shape is deleted or when a different texture is assigned to the shape.

Additionally, the `IShape` interface allows you to draw the current shape on a given image using the `Draw()` method. Drawing follows these rules:

- The position and size of the shape define its bounding rectangle.
- Within the bounding rectangle, a set of points belonging to the shape (the shape’s form) is created. If the shape is a rectangle, its form coincides with the bounding rectangle.
- The texture is applied to the bounding rectangle in such a way that their top-left corners match.
- The pixels of the image that fall inside the shape’s form are filled.
- Pixels that lie at the intersection of the shape's form and the texture are filled with the texture's pixels (if the texture is missing, it can be considered to have zero size).
- The remaining pixels are filled with the default fill symbol, the dot `"."`.
- If some pixels fall outside the image boundaries, they are simply ignored.

As an example of correct drawing, refer to the tests called from the `main()` function in the file `main.cpp`. In the tests, a canvas (an instance of the `Canvas` class) is created. The canvas is essentially an automated graphics editor that is controlled through public methods. For example, the `AddShape()` method adds a new shape using the `MakeShape()` function, which you need to implement. The `DuplicateShape()` method clones an existing shape by calling the `Clone()` method, which you also need to implement. Thus, the tests can be used to verify the correctness of your implementation. However, be careful—just like in other tasks, successfully passing the provided tests is a necessary but not sufficient condition for the correctness of your implementation. Write your solution in the file `Solution.cpp` and submit it for review.