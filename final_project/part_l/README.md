### Programming Task: **Transport Guide, Part L: Uniform Distribution of Intermediate Stops**

---

### Problem Statement

Let’s make the schematic map even neater, once again sacrificing geographical accuracy. Specifically, before calculating the stop projections, we need to recalculate the coordinates of intermediate stops, placing them evenly between **anchor stops** — transfer points and terminal stops.

**Step 1: Identifying Anchor Stops**
Anchor stops include:

* All terminal stops (those where the bus number is shown),
* All transfer stops — i.e., those that are used by more than one bus, or by a single bus **more than twice** in the entire route.

These anchor stops retain their original geographic coordinates. Stops **not served by any bus** also retain their coordinates.

When identifying anchor stops, assume that **non-circular routes** pass through each non-terminal stop an even number of times — once in each direction.
Reminder: a non-circular route `A→B` is equivalent to a circular route `A→B→A` in every respect **except** for determining terminals: in the first case, both `A` and `B` are terminals, while in the second case, only `A` is.

---

**Step 2: Recalculating Coordinates of Intermediate Stops**
For each bus route, identify the anchor stops: the first and last stops and possibly some others. These anchor stops divide the route into **groups** of intermediate stops.

Each group of intermediate stops between two anchor stops must be spaced **evenly** between them.
Let’s say a bus route contains a list of stops `stops`, with stop at index `i` being an anchor, and the next anchor at index `j`. For each stop with index `k` from `i+1` to `j-1`, compute its new **longitude** as:

```
stops[k].lon = stops[i].lon + lon_step * (k - i)
where lon_step = (stops[j].lon - stops[i].lon) / (j - i)
```

The same formula applies to **latitudes**.

---

### Special Cases:

1. **A circular route passes through the same non-terminal stop twice:**
   According to the above rules, it is not considered an anchor. However, its coordinates can be computed in **two different ways**.
   In this case, assume that the **second** (in traversal order) computation is more accurate — i.e., just iterate through all stops and allow coordinate reassignment for intermediate stops.

2. **A circular route with only one anchor stop (a terminal):**
   According to the algorithm, **all stops** on such a route should be located at **the same point** — and that’s exactly what you should do.

---

> **Note:** The new geographic coordinates of intermediate stops affect only their **position on the map**, not the actual **distance between them**, which is used for `Bus` queries.

---

### Final Algorithm for Computing Stop Coordinates on the Map:

1. **Recalculate geographic coordinates** of stops using anchor stops.
2. **Enumerate longitudes and latitudes** in ascending order, merging neighboring ones (from Part K).
3. **Compute x and y coordinates** of stops using coordinate compression based on the numbering from step 2.
