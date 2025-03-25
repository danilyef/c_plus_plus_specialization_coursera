### Programming Assignment: Transport Directory, Part D


In this version, you need to add routing functionality to the transport directory, implemented using the libraries we provide.  


### **Changes to Input Format**  
#### **New Section — `routing_settings`**  
A new key, `"routing_settings"`, is added to the input JSON. Its value is a dictionary with two keys:  

- `"bus_wait_time"` — the time a person waits for a bus at a stop (in minutes). Regardless of when or where they arrive, they will wait exactly this amount of time for any bus. The value is an integer between **1 and 1000**.  
- `"bus_velocity"` — the speed of a bus (in km/h). The speed of all buses is constant and exactly equal to the given value. Stop times at stations, acceleration, and braking times are **not** considered. The value is a floating-point number between **1 and 1000**.  

**Example:**  

```json
"routing_settings": {
  "bus_wait_time": 6,
  "bus_velocity": 40
}
```

This configuration sets the wait time to **6 minutes** and the bus speed to **40 km/h**.  


### **New Query Type — `Route`**  
A new request type `"Route"` is added to the `"stat_requests"` list. These requests build a route between two bus stops. In addition to the usual `"id"` and `"type"`, they contain:  

- `"from"` — the starting stop.  
- `"to"` — the destination stop.  

Both values are names of **existing stops** in the database (though they may not be part of any bus route).  

**Example:**  

```json
{
  "type": "Route",
  "from": "Biryulyovo Zapadnoye",
  "to": "Universam",
  "id": 4
}
```

This request asks for a route from **Biryulyovo Zapadnoye** to **Universam**.  


### **Route Characteristics**  
- A person **can** take multiple buses and **can** use the same bus multiple times.  
- The route **must be optimized for the shortest travel time**.  
- If multiple routes have the same minimal travel time, **any of them can be returned**.  

#### **Time Calculation**  
Two types of time are considered:  

1. **Waiting for a bus** — Always takes exactly `"bus_wait_time"` minutes.  
2. **Riding the bus** — Takes a time equal to the distance divided by `"bus_velocity"`, calculated using road distances (`road_distances`).  

Walking between stops, jumping out of buses, or using other forms of transportation **is not allowed**.  

- **All buses drop passengers off at terminal stops** and go to the depot.  
- Even on circular routes (`"is_roundtrip": true`), passengers **must exit and wait** `"bus_wait_time"` minutes before reboarding.  

---

### **Response Format for `Route` Queries**  
The response consists of:  

- `"request_id"` — The ID of the query.  
- `"total_time"` — The total travel time in **minutes** (floating-point).  
- `"items"` — A list of actions the passenger takes. There are two types of items:  
  - `"Wait"` — Waiting at a stop.  
  - `"Bus"` — Riding a bus for a given number of stops.  

#### **Example Response:**
```json
{
    "request_id": 4,
    "total_time": 11.235,
    "items": [
        {
            "type": "Wait",
            "stop_name": "Biryulyovo Zapadnoye",
            "time": 6
        },
        {
            "type": "Bus",
            "bus": "297",
            "span_count": 2,
            "time": 5.235
        }
    ]
}
```

If there is **no valid route**, return:
```json
{
    "request_id": <query_id>,
    "error_message": "not found"
}
```

### **Your Task**  
1. **Understand graph concepts** and **shortest paths**.  
2. **Design a graph model** where:  
   - **Vertices** and **edges** correspond to transport stops and routes.  
   - The **shortest-weight path** corresponds to the **fastest** bus route.  
3. **Write code** to:  
   - **Build the graph** from the transport directory.  
   - **Extract routes** using the router and **format responses correctly**.  

---

### **Constraints**
- Maximum **100 stops** and **100 bus routes**.  
- Time limit: **3 seconds per test**.  
- Memory limit: **512 MB**.  


### **Notes**

- test_json folder: consists of json files (input, correct output, codes doutput)
- python_helpers: helps to compare json files