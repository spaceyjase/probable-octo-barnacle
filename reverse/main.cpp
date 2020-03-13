#include <iostream>
#include <cstring>

// Reverse a C string 'in place'.
void reverse(char* string)
{
  if (string == nullptr) return;

  char* end = string + strlen(string) - 1;
  char tmp{};
  while (string < end)
  {
    tmp = *string;
    *string++ = *end;
    *end-- = tmp;
  }
}

int main()
{
  {
    char string[] = "hello, world!";
    const std::string expected = "!dlrow ,olleh";
    reverse(string);
    std::cout << std::boolalpha << "Strings matched: " << (expected.compare(string) == 0) << '\n';
  }

  {
    char string[] = "";
    const std::string expected = "";
    reverse(string);
    std::cout << std::boolalpha << "Strings matched: " << (expected.compare(string) == 0) << '\n';
  }

  {
    char* string = nullptr;
    reverse(string);  // calling the function with null doesn't crash...
  }

  return 0;
}