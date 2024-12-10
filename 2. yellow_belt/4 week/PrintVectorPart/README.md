#### Programming Task: Write a class declaration ####

Write a function PrintVectorPart that takes a vector of integers called numbers. This function should search for the first negative number in the vector and print all the numbers located to the left of it in reverse order to the standard output. If the vector does not contain any negative numbers, print all the numbers in reverse order.


```objectivec
void PrintVectorPart(const vector<int>& numbers);

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}

```
