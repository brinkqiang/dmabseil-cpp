#include <iostream>
#include <string>
#include <vector>

// Abseil includes
#include "absl/container/flat_hash_map.h"
#include "absl/strings/str_cat.h"
#include "absl/types/span.h"  // For absl::MakeSpan from absl::base or absl::types depending on version

void demonstrate_str_cat() {
  std::string s1 = "Hello, ";
  std::string s2 = "Abseil!";
  int year = 2025;
  std::string message = absl::StrCat(s1, s2, " Welcome to ", year);
  std::cout << "StrCat Demo: " << message << std::endl;
}

void demonstrate_flat_hash_map() {
  absl::flat_hash_map<std::string, int> word_counts;
  word_counts["apple"] = 5;
  word_counts["banana"] = 10;
  word_counts.insert_or_assign("cherry", 7);

  std::cout << "FlatHashMap Demo:" << std::endl;
  for (const auto& pair : word_counts) {
    std::cout << "  " << pair.first << ": " << pair.second << std::endl;
  }

  if (word_counts.contains("apple")) {
    std::cout << "  Found 'apple'!" << std::endl;
  }
}

void demonstrate_span() {
  std::vector<int> nums = {1, 2, 3, 4, 5};
  absl::Span<const int> num_span = absl::MakeSpan(nums);

  std::cout << "Span Demo (first element): ";
  if (!num_span.empty()) {
    std::cout << num_span.front() << std::endl;
  } else {
    std::cout << "empty" << std::endl;
  }
}

int main() {
  demonstrate_str_cat();
  std::cout << "---------------------" << std::endl;
  demonstrate_flat_hash_map();
  std::cout << "---------------------" << std::endl;
  demonstrate_span();
  return 0;
}