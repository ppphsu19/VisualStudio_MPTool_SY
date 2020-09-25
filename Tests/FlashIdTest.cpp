#include "..\3rd_party\gtest\googletest\include\gtest\gtest.h"
#include "FlashId.h"

TEST(FlashIdTest, ThrowsWhenFlashIdIsGreaterThan8Bytes)
{
	EXPECT_THROW((FlashId{ 1,2,3,4,5,6,7,8,9 }), FlashIdTooLongExpection);
}

TEST(FlashIdTest, PadZerosToSize8)
{
	FlashId id{ 0x01, 0x02 };

	EXPECT_EQ(id.Size(), 8);
}

TEST(FlashIdTest, TestEquality)
{
	FlashId id1{ 0x01, 0x02, 0x03 };
	FlashId id2{ 0x01, 0x02, 0x03 };
	FlashId id3{ 0x01, 0x02 };
	FlashId id4{ 0x01, 0x02, 0x00 };

	EXPECT_TRUE(id1.Equals(id2));
	EXPECT_FALSE(id1.Equals(id3));
	EXPECT_TRUE(id3.Equals(id4));
}