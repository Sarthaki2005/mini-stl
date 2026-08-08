#include<iostream>
#include "hashmap.hpp"
int main()
{
  HashMap<std::string, int> mp;
  mp.insert("Alice", 29);
  mp.insert("Bob", 90);
  mp.insert("Charlie", 91);
  // why return V* if key is not present what to return as val can take any num
  // like val can be -1,-1e9,.....
  int *value = mp.get("Alice");
  if (value)
  {
    std::cout << "Alice: " << *value << "\n";
  }
  else
  {
    std::cout << "Not found\n";
  }
  std::cout << mp.contains("Bob") << "\n";
  std::cout << mp.contains("David") << "\n";
  mp.erase("Bob");
  std::cout << mp.contains("Bob") << "\n";
}
