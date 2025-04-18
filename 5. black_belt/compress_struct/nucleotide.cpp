#include <cstddef>
#include <cstdint>

struct Nucleotide {
  char Symbol;
  size_t Position;
  int ChromosomeNum;
  int GeneNum;
  bool IsMarked;
  char ServiceInfo;
};


struct CompactNucleotide {
  uint32_t Position;
  uint32_t GeneNum : 15;
  uint32_t ServiceInfo : 8;
  uint32_t ChromosomeNum : 6;
  uint32_t Symbol : 2;   
  uint32_t IsMarked : 1;   
};


bool operator == (const Nucleotide& lhs, const Nucleotide& rhs) {
  return (lhs.Symbol == rhs.Symbol)
      && (lhs.Position == rhs.Position)
      && (lhs.ChromosomeNum == rhs.ChromosomeNum)
      && (lhs.GeneNum == rhs.GeneNum)
      && (lhs.IsMarked == rhs.IsMarked)
      && (lhs.ServiceInfo == rhs.ServiceInfo);
}



uint32_t SymbolToBits(char symbol) {
  switch(symbol) {
    case 'A': return 0;
    case 'T': return 1;
    case 'G': return 2;
    case 'C': return 3;
    default: return 0; 
  }
}

char BitsToSymbol(uint32_t bits) {
  switch(bits) {
    case 0: return 'A';
    case 1: return 'T';
    case 2: return 'G';
    case 3: return 'C';
    default: return '?';
  }
}

CompactNucleotide Compress(const Nucleotide& n) {
  CompactNucleotide compact;
  compact.Position = n.Position;
  compact.GeneNum = n.GeneNum;
  compact.ServiceInfo = n.ServiceInfo;
  compact.ChromosomeNum = n.ChromosomeNum;
  compact.Symbol = SymbolToBits(n.Symbol);
  compact.IsMarked = n.IsMarked;
  return compact;
};

Nucleotide Decompress(const CompactNucleotide& cn) {
  Nucleotide n;
  n.Position = cn.Position;
  n.GeneNum = cn.GeneNum;
  n.ServiceInfo = cn.ServiceInfo;
  n.ChromosomeNum = cn.ChromosomeNum;
  n.Symbol = BitsToSymbol(cn.Symbol);
  n.IsMarked = cn.IsMarked;
  return n;
}
