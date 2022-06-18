#include <gtest/gtest.h>
#include <ArgParser.h>

TEST(TestArgumentParser, RegisterFlag){
	ArgParser argParser;

	// Check flag state before operation
	EXPECT_FALSE(argParser.IsFlagRegistered("RandomFlag"));

	//Register flag and call tested function
	argParser.RegisterFlag("RandomFlag");

	//Verify state after opetation
	EXPECT_TRUE(argParser.IsFlagRegistered("RandomFlag"));
}
