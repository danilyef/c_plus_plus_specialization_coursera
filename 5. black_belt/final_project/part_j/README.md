
### **Programming Assignment: Transport Guide, Part J. Coordinate Compression**

### Task

In this part, you need to change the way stop coordinates are calculated on the route map. Specifically, you should move away from geographical accuracy and use **coordinate compression**.

### Coordinate Compression

Let's describe the coordinate compression algorithm using longitudes (x-coordinates) as an example.

First, consider all the longitudes of the stops, sorted in ascending order. It is guaranteed that all longitudes are unique, so there is no need to remove duplicates. The goal is to map the longitudes on the diagram such that:

* The minimum longitude corresponds to the smallest x (equal to `padding`),
* The maximum longitude corresponds to the largest x (equal to `width - padding`),
* The remaining values are evenly spaced in between.

We assign indices to the sorted array of unique longitudes:

* The first gets index 0,
* The second gets index 1,
* The last gets index `lon_count - 1`.

The distance between the x-coordinates of consecutive longitudes is calculated as:
`x_step = (width - 2 * padding) / (lon_count - 1)`.

If there is only one longitude, it should still correspond to the minimum x value (`padding`), as before.

Now, for any given longitude with index `idx`, its x-coordinate on the map is computed as:
`x = idx * x_step + padding`.

The transformations for latitudes (y-coordinates) are analogous, with only one difference in the final formula for the y-coordinate:
`y = height - padding - idx * y_step`.

---

Would you like a visual diagram to better understand the compression process?
