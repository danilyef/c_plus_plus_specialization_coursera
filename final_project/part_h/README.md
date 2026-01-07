
### **Programming Assignment Transport Catalogue, Part H. Bus Numbers on the Map**

---

### Task

In this part, you need to add the bus numbers (names) to the bus route map, labeling them near the terminal bus stops.

---

### Render Settings

Two new settings are added:

| Key                  | Description                             | Value Format                   | Constraints |
|----------------------|-----------------------------------------|---------------------------------|-------------|
| `bus_label_font_size` | Font size for bus names                | Integer                          | > 0 and ≤ 100000 |
| `bus_label_offset`    | Offset for bus names                   | Point (array of 2 numbers)       | ≥ -100000 and ≤ 100000 |

---

### Drawing Bus Names

The names of the buses must be drawn at the terminal bus stops. For a circular route (`"is_roundtrip": true`), the terminal stop is considered to be the first stop on the route. For a non-circular route, the terminal stops are the first and last.

Bus names should be drawn in alphabetical order. Within each bus route, the name should be placed at the first terminal stop first, and if the route is non-circular and the terminals do not coincide, the name should be placed at the second terminal stop.

For each name at a terminal stop, two text objects should be drawn: a translucent background and the name itself.

#### Common properties for both objects:
- Coordinates (`x` and `y`) — corresponding to the stop’s coordinates.
- Offset (`dx` and `dy`) — set by `bus_label_offset`.
- Font size (`font-size`) — set by `bus_label_font_size`.
- Font family (`font-family`) — "Verdana".
- Font weight (`font-weight`) — "bold" (For other SVG objects, `font-weight` should not be present).
- Content — the bus name itself.

#### Additional properties for the background:
- Fill color (`fill`) and stroke color (`stroke`) — set by `underlayer_color`.
- Stroke width (`stroke-width`) — set by `underlayer_width`.
- Line end shape (`stroke-linecap`) and joint shape (`stroke-linejoin`) — both set to "round".

#### Additional property for the name itself:
- Fill color (`fill`) — set to the color corresponding to the bus from the color palette.

---

### Rendering Order

The bus names should be rendered immediately after the bus route lines. The final rendering order should therefore be:

1. Bus route lines.
2. Bus names.
3. Circles representing the stops.
4. Stop names.

---

Let me know if you need any further assistance with this task!