#include <list>
#include <map>
#include <string>
#include <vector>

#include "absl/strings/ascii.h"
#include "absl/strings/match.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "gtest.h"

// --- Test Suite for absl::StrJoin ---
class StrJoinTest : public ::testing::Test {};

TEST_F(StrJoinTest, JoinsVectorOfStrings) {
  std::vector<std::string> v = {"foo", "bar", "baz"};
  EXPECT_EQ(absl::StrJoin(v, "-"), "foo-bar-baz");
}

TEST_F(StrJoinTest, JoinsListOfInts) {
  std::list<int> l = {1, 2, 3};
  EXPECT_EQ(absl::StrJoin(l, ", "), "1, 2, 3");
}

TEST_F(StrJoinTest, JoinsEmptyRange) {
  std::vector<std::string> empty_v;
  EXPECT_EQ(absl::StrJoin(empty_v, "-"), "");
}

TEST_F(StrJoinTest, JoinsMap) {
  std::map<std::string, int> m = {{"one", 1}, {"two", 2}};
  // Note: Order in map for StrJoin depends on std::map's internal ordering
  // (sorted by key)
  std::string joined_map = absl::StrJoin(m, ",", absl::PairFormatter(":"));
  // Possible outputs: "one:1,two:2" or "two:2,one:1" - for map it's sorted
  EXPECT_EQ(joined_map, "one:1,two:2");
}

// --- Test Suite for absl::StrSplit ---
class StrSplitTest : public ::testing::Test {};

TEST_F(StrSplitTest, SplitsStringByChar) {
  absl::string_view sv = "a,b,c";
  std::vector<std::string> v = absl::StrSplit(sv, ',');
  ASSERT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], "a");
  EXPECT_EQ(v[1], "b");
  EXPECT_EQ(v[2], "c");
}

TEST_F(StrSplitTest, SplitsStringByString) {
  std::string s = "alpha--beta--gamma";
  std::vector<absl::string_view> v = absl::StrSplit(s, "--");
  ASSERT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], "alpha");
  EXPECT_EQ(v[1], "beta");
  EXPECT_EQ(v[2], "gamma");
}

TEST_F(StrSplitTest, SplitsWithSkipEmpty) {
  absl::string_view sv = "a,,b,c,";
  std::vector<std::string> v = absl::StrSplit(sv, ',', absl::SkipEmpty());
  ASSERT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], "a");
  EXPECT_EQ(v[1], "b");
  EXPECT_EQ(v[2], "c");
}

TEST_F(StrSplitTest, SplitsToSet) {
  absl::string_view sv = "apple,banana,apple";
  std::set<std::string> s = absl::StrSplit(sv, ',');
  ASSERT_EQ(s.size(), 2);
  EXPECT_TRUE(s.count("apple"));
  EXPECT_TRUE(s.count("banana"));
}

// --- Test Suite for absl::StrReplaceAll ---
class StrReplaceAllTest : public ::testing::Test {};

TEST_F(StrReplaceAllTest, ReplacesSinglePattern) {
  std::string s = "the quick brown fox";
  EXPECT_EQ(absl::StrReplaceAll(s, {{"fox", "cat"}}), "the quick brown cat");
}

TEST_F(StrReplaceAllTest, ReplacesMultipleOccurrencesOfSamePattern) {
  std::string s = "banana bandana";
  std::string r = absl::StrReplaceAll(s, { {"ana", "o"} });
  EXPECT_EQ(r, "bona bando");  // <-- 修正后的预期结果
}

TEST_F(StrReplaceAllTest, ReplacesMultipleDifferentPatterns) {
  std::string s = "hello world example";
  EXPECT_EQ(absl::StrReplaceAll(s, {{"hello", "hi"}, {"world", "earth"}}),
            "hi earth example");
}

TEST_F(StrReplaceAllTest, PatternNotFound) {
  std::string s = "abcde";
  EXPECT_EQ(absl::StrReplaceAll(s, {{"xyz", "123"}}), "abcde");
}

// --- Test Suite for absl::StrContains ---
class StringContainsTest : public ::testing::Test {};

TEST_F(StringContainsTest, ContainsSubstring) {
  absl::string_view text = "The quick brown fox";
  EXPECT_TRUE(absl::StrContains(text, "brown"));
}

TEST_F(StringContainsTest, DoesNotContainSubstring) {
  absl::string_view text = "The quick brown fox";
  EXPECT_FALSE(absl::StrContains(text, "lazy"));
}

TEST_F(StringContainsTest, ContainsChar) {
  absl::string_view text = "example";
  EXPECT_TRUE(absl::StrContains(text, 'm'));
  EXPECT_FALSE(absl::StrContains(text, 'z'));
}

// --- Test Suite for absl::StartsWith ---
class StringStartsWithTest : public ::testing::Test {};

TEST_F(StringStartsWithTest, StartsWithPositive) {
  EXPECT_TRUE(absl::StartsWith("filename.txt", "filename"));
}

TEST_F(StringStartsWithTest, StartsWithNegative) {
  EXPECT_FALSE(absl::StartsWith("filename.txt", "doc"));
}

TEST_F(StringStartsWithTest, StartsWithEmpty) {
  EXPECT_TRUE(absl::StartsWith("abc", ""));  // Any string starts with empty
  EXPECT_TRUE(absl::StartsWith("", ""));     // Empty starts with empty
  EXPECT_FALSE(
      absl::StartsWith("", "a"));  // Empty does not start with non-empty
}

// --- Test Suite for absl::EndsWith ---
class StringEndsWithTest : public ::testing::Test {};

TEST_F(StringEndsWithTest, EndsWithPositive) {
  EXPECT_TRUE(absl::EndsWith("filename.txt", ".txt"));
}

TEST_F(StringEndsWithTest, EndsWithNegative) {
  EXPECT_FALSE(absl::EndsWith("filename.txt", ".doc"));
}

TEST_F(StringEndsWithTest, EndsWithEmpty) {
  EXPECT_TRUE(absl::EndsWith("abc", ""));  // Any string ends with empty
  EXPECT_TRUE(absl::EndsWith("", ""));     // Empty ends with empty
  EXPECT_FALSE(absl::EndsWith("", "a"));   // Empty does not end with non-empty
}

// --- Test Suite for absl::StripPrefix and absl::StripSuffix ---
class StringStripTest : public ::testing::Test {};

TEST_F(StringStripTest, StripsPrefix) {
  absl::string_view input = "prefix_value";
  EXPECT_EQ(absl::StripPrefix(input, "prefix_"), "value");
}

TEST_F(StringStripTest, StripPrefixNotPresent) {
  absl::string_view input = "value_noprefix";
  EXPECT_EQ(absl::StripPrefix(input, "prefix_"), "value_noprefix");
}

TEST_F(StringStripTest, StripsSuffix) {
  absl::string_view input = "value_suffix";
  EXPECT_EQ(absl::StripSuffix(input, "_suffix"), "value");
}

TEST_F(StringStripTest, StripSuffixNotPresent) {
  absl::string_view input = "value_nosuffix";
  EXPECT_EQ(absl::StripSuffix(input, "_suffix"), "value_nosuffix");
}

// --- Test Suite for absl::AsciiStrToLower and absl::AsciiStrToUpper ---
class AsciiCaseConversionTest : public ::testing::Test {};

TEST_F(AsciiCaseConversionTest, ConvertsToLower) {
  EXPECT_EQ(absl::AsciiStrToLower("Hello WORLD 123!"), "hello world 123!");
}

TEST_F(AsciiCaseConversionTest, ConvertsToUpper) {
  EXPECT_EQ(absl::AsciiStrToUpper("Hello world 123!"), "HELLO WORLD 123!");
}

TEST_F(AsciiCaseConversionTest, HandlesEmptyString) {
  EXPECT_EQ(absl::AsciiStrToLower(""), "");
  EXPECT_EQ(absl::AsciiStrToUpper(""), "");
}

TEST_F(AsciiCaseConversionTest, HandlesNonAlphabetic) {
  EXPECT_EQ(absl::AsciiStrToLower("123 !@#"), "123 !@#");
  EXPECT_EQ(absl::AsciiStrToUpper("123 !@#"), "123 !@#");
}