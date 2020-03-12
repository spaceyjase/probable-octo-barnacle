#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

class UniqueFinder
{
public:   
  UniqueFinder() = delete;

  static bool HasAllUniqueCharacters(const std::string& input)
  {
    if (input.empty()) return true;    

    std::unordered_map<std::string::value_type, unsigned> characters;   
    for (auto c : input)
    {
      characters[c]++;
      if (characters[c] > 1) return false; // early return if the current 'c' is not unique
    }

    return std::none_of(characters.cbegin(), characters.cend(), [](auto e) { return e.second > 1; });   
  }
};

int main()
{   
  {   
    bool expected = true;   
    const std::string input{ "" };   
    std::cout << std::boolalpha << "Expected: " << expected << ", got: "    
      << UniqueFinder::HasAllUniqueCharacters(input) << '\n';
  }
  {   
    bool expected = true;
    const std::string input{ "fubar" };
    std::cout << std::boolalpha << "Expected: " << expected << ", got: "
      << UniqueFinder::HasAllUniqueCharacters(input) << '\n';
  }
  {
    bool expected = false;
    const std::string input{ "foobar" };
    std::cout << std::boolalpha << "Expected: " << expected << ", got: "
      << UniqueFinder::HasAllUniqueCharacters(input) << '\n';
  }
  std::cout << "Done!\n";
  return 0;
}
