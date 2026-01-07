### **Programming Assignment: Transport Catalogue, Part M. Advanced Merging of Adjacent Coordinates**

---

### Task

In this part, you need to implement an **advanced numbering algorithm** for latitudes and longitudes that preserves the relative order of stops within a single route while allowing a cleaner map layout.

---

### Numbering Rules

1. The **first (minimum) longitude** is assigned number `0`.  
2. For each subsequent longitude:
   - If it has **no route neighbors** among previously numbered (smaller) longitudes, its number is `0`.  
   - If it has **route neighbors** among the smaller longitudes, its number is equal to **the number of the largest smaller route neighbor plus 1**.  

The same rules apply to latitudes.  

---

### Examples

```python
# Example 1: stops on different routes
longitudes = [50.1, 50.2, 50.3, 50.4]
# Numbering: all 0 because no route neighbors exist
numbers = [0, 0, 0, 0]

# Example 2: stops on two routes
route_1 = [50.1, 50.2]
route_2 = [50.3, 50.4]
# Numbering: 50.1 -> 0, 50.2 -> 1 (neighbor 50.1), 50.3 -> 0, 50.4 -> 1 (neighbor 50.3)
numbers = [0, 1, 0, 1]
