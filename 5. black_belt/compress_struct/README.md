
### **Programming Assignment: Nucleotide: Data Structure Compression**

### Problem Statement

In a program used for human genome research, the following data structure is used to store and transmit information about nucleotides found in the genome:

```cpp
struct Nucleotide {
  char Symbol;
  size_t Position;
  int ChromosomeNum;
  int GeneNum;
  bool IsMarked;
  char ServiceInfo;
};
```

Where:

- **Symbol** – the common letter code of one of the four nucleotides: A, T, G, or C.
- **Position** – the position of the found nucleotide in the genome. Can take values from 0 to 3.3 billion.
- **ChromosomeNum** – the chromosome number where the nucleotide was found. Can range from 1 to 46.
- **GeneNum** – the gene number where the nucleotide was found. Can range from 1 to 25,000, and also includes the special value 0 if the nucleotide lies outside known genes.
- **IsMarked** – a flag indicating whether the found nucleotide was previously marked.
- **ServiceInfo** – service information related to the search result. Can be any character.

The program works correctly, but the search results consume too much memory.

Your task, using the knowledge acquired in lectures, is to write a data structure `CompactNucleotide` that stores the same information (without loss) **in a more compact form**.

To ensure compatibility, you are also required to implement the functions `Compress()` and `Decompress()`.

### Requirements:

- The size of your `CompactNucleotide` structure must **not exceed 8 bytes**.
- You **may not use** the `#pragma pack` directive in your solution.

---

Let me know if you'd like help with implementing the compact version!