### Programming Assignment: Transport Directory, Part B

Implement the second version of the task with the following changes.

The database now contains data on the actual measured road distance between stops.

**Stop X (Changes in the stop addition query)**  
The new format for the stop addition query is:  
**Stop X: latitude, longitude, D1m to stop1, D2m to stop2, ...**  

That is, now after the latitude and longitude, a list of distances from this stop to neighboring stops can follow. By default, it is assumed that the distance from X to stop# is the same as the distance from stop# to X, unless the distance from stop# to X is explicitly specified during the addition of stop#.

It is guaranteed that each of the stops stop# is defined in some Stop query.  
Within a single Stop query, all stop# are distinct, and their number does not exceed 100.  

All Di are positive integers, each of which does not exceed 1,000,000 and is not less than the straight-line distance between the corresponding stops. After each distance, the letter "m" must follow.

**Bus X (Changes in the bus information query)**  
The new format for the bus information query response is:  
**Bus X: R stops on route, U unique stops, L route length, C curvature**  

Now, L is calculated using road distance rather than geographical coordinates.

C (curvature) is the ratio of the route length calculated using road distance (new L) to the route length calculated using geographical distance (L from the previous versions of the task). Thus, C is a real number greater than one. It can only be equal to one if the bus travels between stops along the shortest path (in which case it’s more like a helicopter), and less than one can only occur due to teleportation or chord tunnels.

It is guaranteed that for any two neighboring stops on any route, the road distance between them is provided in some way.

**Example**  
Input:
```
13
Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino
Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam
Stop Biryusinka: 55.581065, 37.64839, 750m to Universam
Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
```

**Output:**
```
Bus 256: 6 stops on route, 5 unique stops, 5950 route length, 1.361239 curvature
Bus 750: 5 stops on route, 3 unique stops, 27600 route length, 1.318084 curvature
Bus 751: not found
Stop Samara: not found
Stop Prazhskaya: no buses
Stop Biryulyovo Zapadnoye: buses 256 828
```