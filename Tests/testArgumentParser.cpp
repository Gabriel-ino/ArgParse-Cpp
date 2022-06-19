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

TEST(TestArgumentParser, RegisterFlag_With_Whitespace){
	ArgParser argParser;
	argParser.RegisterFlag("Random Flag");
	
	EXPECT_FALSE(argParser.IsFlagRegistered("Random Flag"));
}

TEST(TestArgumentParser, RegisterFlag_Whitespace_Only){
	ArgParser argParser;
	argParser.RegisterFlag(" ");
	EXPECT_FALSE(argParser.IsFlagRegistered(" "));

}

TEST(TestArgumentParser, RegisterOption){
	ArgParser argParser;
	argParser.RegisterOption("NewOption");

	EXPECT_TRUE(argParser.IsOptionRegistered("NewOption"));
}

TEST(TestArgumentParser, RegisterOption_With_Whitespace){
	ArgParser argParser;
	argParser.RegisterOption("New Option");

	EXPECT_FALSE(argParser.IsOptionRegistered("New Option"));
}
