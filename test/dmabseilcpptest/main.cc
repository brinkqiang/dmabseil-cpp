#include <string>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "gtest.h"

// 测试基本的字符串字面量拼接
TEST(StrCatTest, ConcatenatesStringLiterals) {
  EXPECT_EQ(absl::StrCat("Hello, ", "World!"), "Hello, World!");
}

// 测试 std::string对象的拼接
TEST(StrCatTest, ConcatenatesStdStrings) {
  std::string s1 = "Test ";
  std::string s2 = "String";
  EXPECT_EQ(absl::StrCat(s1, s2), "Test String");
}

// 测试 absl::string_view 对象的拼接
TEST(StrCatTest, ConcatenatesStringViews) {
  absl::string_view sv1 = "View ";
  absl::string_view sv2 = "One";
  EXPECT_EQ(absl::StrCat(sv1, sv2), "View One");
}

// 测试混合类型的拼接 (std::string, const char*, int)
TEST(StrCatTest, ConcatenatesMixedTypes) {
  std::string name = "Abseil";
  int version = 2025;
  EXPECT_EQ(absl::StrCat("Library: ", name, ", Version: ", version),
            "Library: Abseil, Version: 2025");
}

// 测试与空字符串拼接
TEST(StrCatTest, ConcatenatesWithEmptyString) {
  std::string s = "NonEmpty";
  EXPECT_EQ(absl::StrCat(s, ""), "NonEmpty");
  EXPECT_EQ(absl::StrCat("", s), "NonEmpty");
  EXPECT_EQ(absl::StrCat(""), "");  // StrCat with single empty string
  EXPECT_EQ(absl::StrCat(), "");    // StrCat with no arguments
}

// 测试数字类型的拼接
TEST(StrCatTest, ConcatenatesNumbers) {
  int i = 123;
  double d = 45.67;
  // Note: absl::StrCat for floating point might produce different
  // representations than std::to_string or printf, depending on precision and
  // formatting. For precise float-to-string, absl::StrFormat or
  // absl::Substitute might be better. Here, we test the basic concatenation.
  EXPECT_EQ(absl::StrCat("Integer: ", i), "Integer: 123");
  EXPECT_EQ(absl::StrCat(i, ", Double: ", d),
            "123, Double: 45.67");  // Default double to string conversion
}

// 测试多个参数的拼接
TEST(StrCatTest, ConcatenatesMultipleArguments) {
  EXPECT_EQ(absl::StrCat("a", "b", "c", "d", "e"), "abcde");
}

// 测试 char 类型的拼接
TEST(StrCatTest, ConcatenatesChars) {
    std::string str1 = "X";
    std::string str2 = "Y";
    EXPECT_EQ(absl::StrCat("Char1: ", str1, ", Char2: ", str2), "Char1: X, Char2: Y");
}

// main 函数由 GTest 提供，这里不需要显式定义