### Programming Assignment: **Transport Directory, Part F. SVG Output Library**  

In this task, you need to create a simple library for generating vector images in SVG format. The main use of this library in the course is the visualization of the "Transport Directory." Therefore, you only need to implement three types of objects:  

- **Circle**: Defined by the coordinates of its center and its radius.  
- **Polyline**: Defined by a sequence of vertex coordinates.  
- **Text**: Defined by text content, reference point coordinates, offset relative to the reference point, font size, and font name.  

Additionally, all object types must have the following properties:  
- Stroke color and fill color  
- Stroke width  
- Line cap style and line join type  

The entire library must reside in the `Svg` namespace.  

### Example Usage  
```cpp
Svg::Document svg;

svg.Add(
    Svg::Polyline{}
    .SetStrokeColor(Svg::Rgb{140, 198, 63})  // soft green
    .SetStrokeWidth(16)
    .SetStrokeLineCap("round")
    .AddPoint({50, 50})
    .AddPoint({250, 250})
);

for (const auto point : {Svg::Point{50, 50}, Svg::Point{250, 250}}) {
  svg.Add(
      Svg::Circle{}
      .SetFillColor("white")
      .SetRadius(6)
      .SetCenter(point)
  );
}

svg.Add(
    Svg::Text{}
    .SetPoint({50, 50})
    .SetOffset({10, -10})
    .SetFontSize(20)
    .SetFontFamily("Verdana")
    .SetFillColor("black")
    .SetData("C")
);
svg.Add(
    Svg::Text{}
    .SetPoint({250, 250})
    .SetOffset({10, -10})
    .SetFontSize(20)
    .SetFontFamily("Verdana")
    .SetFillColor("black")
    .SetData("C++")
);

svg.Render(std::cout);
```

### Expected Output  
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<svg xmlns="http://www.w3.org/2000/svg" version="1.1">
    <polyline points="50,50 250,250 " fill="none" stroke="rgb(140,198,63)" stroke-width="16" stroke-linecap="round" />
    <circle cx="50" cy="50" r="6" fill="white" stroke="none" stroke-width="1" />
    <circle cx="250" cy="250" r="6" fill="white" stroke="none" stroke-width="1" />
    <text x="50" y="50" dx="10" dy="-10" font-size="20" font-family="Verdana" fill="black" stroke="none" stroke-width="1">C</text>
    <text x="250" y="250" dx="10" dy="-10" font-size="20" font-family="Verdana" fill="black" stroke="none" stroke-width="1">C++</text>
</svg>
```

---

### Required Helper Classes  

#### **Point**  
- A structure with two `double` fields: `x` and `y`.  
- Can be initialized using `Point{x, y}`.  
- Supports default construction and direct field access.  

#### **Rgb**  
- A structure with three integer fields: `red`, `green`, and `blue`.  
- Can be initialized using `Rgb{red, green, blue}`.  
- Values range from `0` to `255` (validation not required).  

#### **Color**  
A type that can be initialized in three ways:  
1. **Default constructor** → Outputs `"none"`.  
2. **String (`std::string`)** → Outputs the string directly.  
3. **`Rgb` structure** → Outputs as `rgb(red,green,blue)`.  

- Must support implicit initialization with a string or `Rgb`.  
- A global constant `Svg::NoneColor` should be defined as an instance of `Color` using the default constructor (similar to `std::nullopt`).  

---

### **Document Class**
Handles the composition and rendering of an SVG document. It must support:  

1. **Default construction**: `Svg::Document svg;`  
2. **Adding objects**: `svg.Add(object);`  
   - `object` must be of type `Circle`, `Polyline`, or `Text`.  
   - Objects are stored in a linear structure (like an array).  
3. **Rendering the document**: `svg.Render(out);`  
   - `out` is an `std::ostream` subclass.  

---

### **Property Methods for Objects**
Objects must support default construction and the following property-setting methods. Each method should take exactly **one** parameter.  

#### **Common Methods**  
- `SetFillColor(const Color&)` → Sets `fill` color (default: `NoneColor`).  
- `SetStrokeColor(const Color&)` → Sets `stroke` color (default: `NoneColor`).  
- `SetStrokeWidth(double)` → Sets `stroke-width` (default: `1.0`).  
- `SetStrokeLineCap(const string&)` → Sets `stroke-linecap` (not outputted by default).  
- `SetStrokeLineJoin(const string&)` → Sets `stroke-linejoin` (not outputted by default).  

#### **Circle**  
- `SetCenter(Point)` → Sets `cx` and `cy` (default: `0.0`).  
- `SetRadius(double)` → Sets `r` (default: `1.0`).  

#### **Polyline**  
- `AddPoint(Point)` → Adds a vertex to the polyline. The `points` attribute should be formatted as `"x,y x,y ..."` (default: empty string).  

#### **Text**  
- `SetPoint(Point)` → Sets `x` and `y` (default: `0.0`).  
- `SetOffset(Point)` → Sets `dx` and `dy` (default: `0.0`).  
- `SetFontSize(uint32_t)` → Sets `font-size` (default: `1`).  
- `SetFontFamily(const string&)` → Sets `font-family` (not outputted by default).  
- `SetData(const string&)` → Sets the content of the `<text>` tag (default: empty).  

---

### **Rendering Rules**
The `Svg::Document::Render` method should generate output in the following structure:  
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<svg xmlns="http://www.w3.org/2000/svg" version="1.1">
    <!-- Objects added with svg.Add() appear here -->
</svg>
```
- Properties should be formatted as `name="value"`.  
- Extra whitespace is allowed:  
  - Between tags.  
  - Between properties.  
  - Around `=` in attribute assignments.  
  - Between coordinate values.  

#### **Specific Object Formatting**  
- **Circle** → `<circle ... />`  
- **Polyline** → `<polyline ... />`  
- **Text** → `<text ...>content</text>`  

---

### **Additional Requirements**
- The library may include additional helper classes for maintainability.  
- Objects must only support **their own** property methods (e.g., `Svg::Text{}.SetRadius(0)` should **not** compile).  
- Move semantics are optional but recommended for `svg.Add(move(polyline))`.  
- **String escaping is not required**—output raw strings as-is.  
- Floating-point numbers should use the **standard formatting** (no special precision settings).  
- Performance: The solution must handle **100,000 object constructions and method calls** within **1 second**, plus one `Render` call.  

This ensures efficient rendering of large-scale SVG documents while keeping the code readable and modular. 🚀