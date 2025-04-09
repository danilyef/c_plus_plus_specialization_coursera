
### **Programming Assignment: Transport Catalogue, Part G. Basic Bus Map**

---

### Task

In this part, you need to build the first version of a bus route map in **SVG format**. The map should be returned in response to a new request type in the database — **Map**:

```json
"stat_requests": [
  /* ... */
  {
    "id": 999,
    "type": "Map"
  }
]
```

The response to a Map request contains a single key `"map"` with the SVG document as a string:

```json
{
  "map": "<?xml version=\"1.0\" encoding=\"UTF-8\" ?><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\"></svg>"
}
```

Be sure to **escape special characters** when outputting strings in JSON: quotes `"` and backslashes `\`.

---

### Extended SVG Format Support

To build the map, the library from Part F is sufficient **except for one extension**:  
Colors may now be specified not only as strings or RGB arrays but also in **RGBA format** (RGB with alpha channel): `rgba(red, green, blue, alpha)` (see examples).  
The alpha channel is compared for correctness using an **absolute tolerance of 1e-6**.

You are **not required** to use the library from the previous part.  
However, the final SVG document **must still meet all previous format requirements**.

---

### Render Settings

A new key, `"render_settings"`, is added to the input. Its value is a dictionary specifying the rendering configuration:

| Key                  | Description                             | Value Format                   | Constraints |
|----------------------|-----------------------------------------|---------------------------------|-------------|
| `width`              | Max width of the map                    | Floating-point number            | > 0 and ≤ 100000 |
| `height`             | Max height of the map                   | Floating-point number            | > 0 and ≤ 100000 |
| `padding`            | Padding from the edges of the map       | Floating-point number            | ≥ 0 and < min(width, height)/2 |
| `stop_radius`        | Radius of stop circles                  | Floating-point number            | > 0 and ≤ 100000 |
| `line_width`         | Bus route line thickness                | Floating-point number            | > 0 and ≤ 100000 |
| `stop_label_font_size` | Font size for stop names              | Integer                          | > 0 and ≤ 100000 |
| `stop_label_offset`  | Offset for stop name text               | Array of 2 floating-point numbers| Between -100000 and 100000 |
| `underlayer_color`   | Background color for text               | Color (see below)                | - |
| `underlayer_width`   | Background stroke width for text        | Floating-point number            | > 0 and ≤ 100000 |
| `color_palette`      | Route color palette                     | Array of colors                  | Non-empty, ≤ 100 elements |

---

### Color Description in JSON

Colors can be described in three formats:

- **String**: e.g., `"green"` (non-empty, only lowercase Latin letters, max length 20).
- **RGB Array**: e.g., `[0, 255, 0]` (each number in range [0, 255]).
- **RGBA Array**: e.g., `[0, 255, 0, 0.5]` (first 3 numbers in [0, 255], last in [0, 1]).

It’s guaranteed that every color uses one of these three formats.

---

### Rendering Algorithm

To ensure your program can be automatically validated, you **must strictly follow** the rendering order and projection logic.

The map consists of **three types of objects**, rendered in the following order:

1. **Polylines** for bus routes
2. **Circles** for bus stops
3. **Text** for stop names

Unless stated otherwise, SVG object properties should default to those used in Part F.

---

### Coordinate Projection

A core task is projecting key points (i.e., bus stops) from geographical coordinates (latitude and longitude) onto map coordinates (`Svg::Point`). The settings used here are `width`, `height`, and `padding`.

Projection is based on scaling longitude and latitude to fit within a rectangle of size `(width - 2 * padding) × (height - 2 * padding)`.

Steps:

1. Calculate min and max latitude and longitude: `min_lat`, `min_lon`, `max_lat`, `max_lon`.

   - The stop with the smallest longitude maps to `x = padding`.
   - The northernmost stop (largest latitude) maps to `y = padding`.

2. Compute zoom coefficients:

   - `width_zoom_coef = (width - 2 * padding) / (max_lon - min_lon)`
   - `height_zoom_coef = (height - 2 * padding) / (max_lat - min_lat)`

3. Choose `zoom_coef` as the **minimum** of these two.

   - If one zoom_coef results in division by zero, use the other.
   - If both divisions are zero (all stops at the same coordinates), then `zoom_coef = 0`.

4. Final coordinate formulas:

```text
x = (lon - min_lon) * zoom_coef + padding;
y = (max_lat - lat) * zoom_coef + padding;
```

---

### Bus Color Assignment

- Colors for bus lines come from the `color_palette`.
- Buses are sorted **alphabetically** by name.
- The first bus gets the first color, the second gets the second, etc.
- If buses outnumber palette colors, reuse colors cyclically.

---

### Drawing Bus Routes

- Render in ascending order by **bus name**.
- Each route is a **polyline**:

  | Property         | Value                          |
  |------------------|--------------------------------|
  | `stroke`         | Assigned from `color_palette`  |
  | `stroke-width`   | `line_width`                   |
  | `stroke-linecap` | `"round"`                      |
  | `stroke-linejoin`| `"round"`                      |

- Points are coordinates of the route stops.
- For non-circular routes (`"is_roundtrip": false`), each segment is drawn **twice**.

---

### Drawing Bus Stops

- Render **one circle per stop**, sorted by stop name.
- Each circle has:

  | Property | Value                        |
  |----------|------------------------------|
  | `cx, cy` | Stop's coordinates           |
  | `r`      | `stop_radius`                |
  | `fill`   | `"white"`                    |

---

### Drawing Stop Names

- Render **one name per stop**, sorted by stop name.
- Each stop gets two text elements:

  1. **Underlayer (background)**  
  2. **Actual name text**

- Common properties:

  | Property      | Value                                 |
  |---------------|----------------------------------------|
  | `x, y`        | Stop coordinates                      |
  | `dx, dy`      | `stop_label_offset`                   |
  | `font-size`   | `stop_label_font_size`                |
  | `font-family` | `"Verdana"`                           |
  | Content       | Stop name                             |

- Underlayer additional properties:

  | Property         | Value                 |
  |------------------|-----------------------|
  | `fill`           | `underlayer_color`    |
  | `stroke`         | `underlayer_color`    |
  | `stroke-width`   | `underlayer_width`    |
  | `stroke-linecap` | `"round"`             |
  | `stroke-linejoin`| `"round"`             |

- Main label additional property:

  | Property | Value   |
  |----------|----------|
  | `fill`   | `"black"` |

---

Let me know if you'd like this as a downloadable document or need help implementing it!