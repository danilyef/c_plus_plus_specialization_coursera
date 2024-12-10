### Programming Task: Mass of Blocks 

Calculate the total mass of cuboid-shaped concrete blocks of the same density but different sizes.

### Note 
Assume that block sizes are measured in centimeters, density is measured in grams per cubic centimeter, and the final mass is measured in grams. Thus, the mass of a block can be calculated as a simple product of density and volume.

### Input format 
The first line contains two positive integers: the number of blocks _N_ and the density of each block _R_. Each of the following _N_ lines contains three positive integers _W_, _H_, _D_ — the sizes of the next block.

It is guaranteed that:

- the number of blocks _N_ does not exceed 10^5;
- block density _R_ does not exceed 100;
- block sizes _W_, _H_, _D_ do not exceed 10^4.

### Example 

**Input**
```commandline
2 14
1 2 3
30 40 50
```

    **Output**
```commandline
840084
```
