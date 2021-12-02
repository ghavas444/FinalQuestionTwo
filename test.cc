#include "char.h"

TEST(countCharTest, ValidEntry) {
  EXPECT_EQ(0, countChar(""));
  EXPECT_EQ(3, countChar("Two"));
  EXPECT_EQ(5, countChar("Three"));
}

TEST(countCharTest, Spaces) {
	EXPECT_EQ(7, countChar("Does it"));
	EXPECT_EQ(12, countChar("Work or does"));
	EXPECT_EQ(11, countChar("it not work"));
}

TEST(countCharTest, SpecialCharacters) {
	EXPECT_EQ(7, countChar(",,,,,,,"));
	EXPECT_EQ(6, countChar("@#$@%#"));
	EXPECT_EQ(8, countChar("()()&*%%"));
}