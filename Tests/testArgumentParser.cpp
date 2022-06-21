#include <gtest/gtest.h>
#include <utils.h>
#include <ArgParser.h>
#include <array>
#include <string>
#include <stdexcept>
#include <limits.h>

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

TEST(TestArgumentParser, Parse){
	ArgParser argParser;

	//Simulating arguments passed to the software
	std::array<const char*, 5> args = {
		"TestArgumentParser",
		"--flag",
		"--string=AaBbCcDd",
		"--number=42",
		"--float=4.2"
	};

	argParser.RegisterFlag("flag");
	argParser.RegisterOption("string");
	argParser.RegisterOption("number");
	argParser.RegisterOption("float");

	argParser.Parse(static_cast<int>(args.size()), args.data());
	
	//Verify passed Flag
	EXPECT_FALSE(argParser.GetFlag("unregisteredFlag"));
	EXPECT_TRUE(argParser.GetFlag("flag"));
	EXPECT_EQ(argParser.GetOptionAsString("string"), "aabbccdd");
	EXPECT_EQ(argParser.GetOptionAsInt("number"), 42);
	EXPECT_EQ(argParser.GetOptionAsFloat("float"), 4.2f);


}

TEST(testArgumentParser, Parse_Invalid_Arguments_){
	ArgParser argParser;
	
	argParser.Parse(0, nullptr);
	argParser.Parse(42, nullptr);
	argParser.Parse(-1, nullptr);
	try{
		argParser.Parse(INT_MAX + 1, nullptr);
	
	}catch(std::invalid_argument& err){
		EXPECT_EQ(err.what(), std::string("For security purposes, this value isn't permitted"));
	}
}
