
### **Programming Assignment: Transport Catalogue, Part I. Managing Map Layers**

---

### Task

In this part, you need to support the management of map layers: their presence and relative order.

A new rendering setting is added:

| Key      | Description                           | Value Format   | Constraints                              |
|----------|---------------------------------------|----------------|------------------------------------------|
| `layers` | Names of layers to display on the map | Array of strings | Each string is a valid layer name, no more than 10 entries |

---

### Available Layer Names

The layer names can be the following:

- `"bus_lines"` — bus route lines.
- `"bus_labels"` — bus names.
- `"stop_points"` — stop circles.
- `"stop_labels"` — stop names.

---

### Layer Rendering Order

The rendering order of layers is now **determined solely by the `layers` setting**. Additionally, if any of the 4 layers is missing from the list, it should **not be rendered**. For example, if `"layers": ["bus_lines", "stop_points", "stop_labels"]`, the map will correspond exactly to Part G.

If a layer is specified multiple times, it should be rendered the corresponding number of times. For example, with `"layers": ["bus_lines", "stop_points", "bus_lines"]`, bus lines will be drawn both **under** and **above** the stop circles.

If the `layers` array is empty, the map should contain no objects inside the `<svg>` tag.

---

Let me know if you need further clarification or help with implementing this part!