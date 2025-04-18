### Programming Assignment: **Transport Directory under Sanitizers**  

You are given a solution for Part E of the "Transport Directory" from the "Brown Belt." This solution contains some issues that can be detected using sanitizers and/or debugging defines. Your task is to find these issues, fix them, and submit the corrected solution.  

**File:** `original.zip`  

The requirements for this task are identical to those of Part E, except for the following constraints:  

- The database can contain up to **650 buses** and **650 stops**.  
- The number of queries to the large database may not be at the maximum limit, ensuring that the solution with the given router successfully passes the tests.  
- **Time limit:** 2 seconds.  
- **Memory limit:** 1 GB.  

As a result, the router in the given solution is structured differently, and the original solution for Part E **cannot** be submitted for this task without modifications.


**My Solution:**


### Error 1: Dereferencing an Invalidated Iterator  

```cpp
std::optional<typename Router<Weight>::RouteInfo> Router<Weight>::BuildRoute(VertexId from, VertexId to) const {
  // ...
  std::set<std::pair<Weight, VertexId>> vertices_by_weight{{0, from}};
  std::unordered_set<VertexId> done_vertices;

  while (!vertices_by_weight.empty()) {
    const auto min_vertex_it = vertices_by_weight.begin();
    vertices_by_weight.erase(min_vertex_it);
    done_vertices.insert(min_vertex_it->second);
    // ...
  }
  
  // ...
}
```
Here, the iterator `min_vertex_it` is dereferenced **after** being passed to `erase`, leading to access of freed heap memory. I saved values before ereasing the iterator, in order to reuse them later.

---

### Error 2: Confusion Between `reserve` and `resize`  

```cpp
TransportRouter::TransportRouter(const Descriptions::StopsDict& stops_dict,
                                 const Descriptions::BusesDict& buses_dict,
                                 const Json::Dict& routing_settings_json)
    : routing_settings_(MakeRoutingSettings(routing_settings_json))
{
  const size_t vertex_count = stops_dict.size() * 2;
  vertices_info_.reserve(vertex_count);
  // ...
}
```
Here, `reserve` is mistakenly used instead of `resize`. Later in the code, `vertices_info_` is accessed by index while the vector is still empty. Although memory is allocated with `reserve`, accessing elements by index results in **out-of-bounds access**.

---

### Error 3: Out-of-Bounds Access in Another Vector  

```cpp
void TransportRouter::FillGraphWithBuses(
    const Descriptions::StopsDict& stops_dict,
    const Descriptions::BusesDict& buses_dict) {
  for (const auto& [_, bus_item] : buses_dict) {
    // ...
    for (size_t start_stop_idx = 0;
         start_stop_idx + 1 < stop_count;
         ++start_stop_idx) {
      const Graph::VertexId start_vertex =
          stops_vertex_ids_[bus.stops[start_stop_idx]].in;
      int total_distance = 0;
      for (size_t finish_stop_idx = start_stop_idx + 1;
           finish_stop_idx <= stop_count;
           ++finish_stop_idx) {  // Error: should be <
        // ...
      }
    }
  }
}
```
In the inner `for` loop, the stopping condition mistakenly uses `<=` instead of `<`. This can leads ti `bus.stops[stop_count]` **out of bounds** error.  

---

### Error 4: Another Out-of-Bounds Vector Access  

```cpp
template <typename Weight>
EdgeId DirectedWeightedGraph<Weight>::AddEdge(const Edge<Weight>& edge) {
  edges_.push_back(edge);
  const EdgeId id = edges_.size();  // Error: should be edges_.size() - 1
  incidence_lists_[edge.from].push_back(id);
  return id;
}
```
Here, we need to compute `edges_.size()` for new edge `id` first, before inserting it into the vector of edges. Without it, retrieving an edge by `edge_id` works incorrectly, and for the last edge, it causes **out-of-bounds access**.

