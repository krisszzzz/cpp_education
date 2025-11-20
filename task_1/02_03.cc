#include <iostream>

int main() {
  int input_char = std::cin.get();
  if (std::cin.fail() || input_char == EOF) {
    std::cout << "Expected character\n";
    return -1;
  }
  char c = static_cast<char>(input_char);
  switch (c) {
  case 'A' ... 'Z':
    std::cout << "uppercase letter\n";
    break;
  case 'a' ... 'z':
    std::cout << "lowercase letter\n";
    break;
  case '0' ... '9':
    std::cout << "decimal digit\n";
    break;
  case '!':
  case '"':
  case '\'':
  case '(':
  case ')':
  case ',':
  case '-':
  case '.':
  case ':':
  case ';':
  case '?':
    std::cout << "punctuation mark\n";
    break;
  default:
    std::cout << "other character\n";
    break;
  }
  return 0;
}