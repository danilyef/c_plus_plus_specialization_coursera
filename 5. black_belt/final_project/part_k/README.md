
### **Programming Task: Transport Guide, Part K. Coordinate Compression with Neighbor Merging**

### Problem Statement

We aim to improve the coordinate compression algorithm using the following idea: if neighboring longitudes (or latitudes) in a sorted set are not directly connected by a segment of a bus route passing through the corresponding stops, these longitudes (latitudes) can be assigned the same number and, consequently, the same x-coordinate (y-coordinate).

### Coordinate Numbering

Let’s describe the algorithm for numbering longitudes based on the sorted array of their values.

The first (smallest) longitude is assigned the number 0. Then, iterating through longitudes in ascending order, for each longitude, we decide whether to assign it the same number as the previous one or to finish the current group of longitudes corresponding to a single x-coordinate and assign the current longitude a number one greater than the previous.

Let’s denote the number of the previous longitude as `idx`. The current longitude should be assigned the same number `idx` if none of the previous longitudes with number `idx` is a route neighbor of the current longitude. **Route neighbors** are pairs of longitudes corresponding to stops that are adjacent stops of some bus route.

The algorithm for latitudes is completely analogous.

### Coordinate Mapping

Changes in this part are minimal:

The values of `x_step` and `y_step` are calculated using the numbers of the last longitude (`max_lon_idx`) and the last latitude (`max_lat_idx`):
`x_step = (width - 2 * padding) / max_lon_idx`,
`y_step = (height - 2 * padding) / max_lat_idx`.
As before, if the denominator is zero, the result of the expression can be considered zero.

The formulas for the final x- and y-coordinates are completely analogous and use the longitude and latitude numbers from the previous section.
