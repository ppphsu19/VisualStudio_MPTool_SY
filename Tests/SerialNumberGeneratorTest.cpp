#include "..\3rd_party\gtest\googletest\include\gtest\gtest.h"
#include "SerialNumberGenerator.h"

TEST(SerialNumberGeneratorTest, ThrowsWhenConstructorParemetersHaveDifferentStringLength)
{
	EXPECT_THROW((SerialNumberGenerator{ "SN01", "SN0100", "SN0###" }), InconsistentLengthException);
}

TEST(SerialNumberGeneratorTest, ThrowsWhenOffsetIsGreaterThanTotalAvailableSerialNumberCount)
{
	EXPECT_THROW((SerialNumberGenerator{ "SN01", "SN05", "SN0#", 6 }), OffsetOutOfRangeException);
}

TEST(SerialNumberGeneratorTest, ThrowsWhenThereIsDifferentCharacterAtNonMaskSymbolPosition)
{
	EXPECT_THROW((SerialNumberGenerator{ "SN0001", "SN1100", "SN0###" }), MaskSettingErrorException);
}

TEST(SerialNumberGeneratorTest, ThrowsWhenThereIsNoAvailableSerialNumerToReturn)
{
	SerialNumberGenerator sng{ "SN001", "SN005", "SN00#", 5 };

	EXPECT_THROW(sng.GetSerialNumber(), NoAvailableSerialNumberException);
}

TEST(SerialNumberGeneratorTest, ReturnsAmountOfUnusedSerialNumber)
{
	SerialNumberGenerator sng{ "SN001", "SN050", "SN0##" };

	EXPECT_EQ(sng.GetRemainingSerialNumberCount(), 50);

	auto notUsed = sng.GetSerialNumber();
	EXPECT_EQ(sng.GetRemainingSerialNumberCount(), 49);
}

TEST(SerialNumberGeneratorTest, ReturnSerialNumberGivenSpecificOffset)
{
	SerialNumberGenerator sng{ "SN001", "SN050", "SN0##", 6 };

	EXPECT_EQ(sng.GetSerialNumber(), "SN007");
}

TEST(SerialNumberGeneratorTest, ReturnSerialNumberIncrementally)
{
	SerialNumberGenerator sng{ "SN0001", "SN0100", "SN0###" };

	std::string serialNum = sng.GetSerialNumber();
	EXPECT_EQ(serialNum, "SN0001");

	serialNum = sng.GetSerialNumber();
	EXPECT_EQ(serialNum, "SN0002");
}

TEST(SerialNumberGeneratorTest, ReturnSerialNumberDecrementally)
{
	SerialNumberGenerator sng{ "SN0100", "SN0001", "SN0###" };

	std::string serialNum = sng.GetSerialNumber();
	EXPECT_EQ(serialNum, "SN0100");

	serialNum = sng.GetSerialNumber();
	EXPECT_EQ(serialNum, "SN0099");
}

TEST(SerialNumberGeneratorTest, MaskSymbolsAreNotContinuous)
{
	SerialNumberGenerator sng{ "SN00abc9", "SN10abc0", "SN##abc#" };

	EXPECT_EQ(sng.GetSerialNumber(), "SN00abc9");
	EXPECT_EQ(sng.GetSerialNumber(), "SN01abc0");
	EXPECT_EQ(sng.GetSerialNumber(), "SN01abc1");
}