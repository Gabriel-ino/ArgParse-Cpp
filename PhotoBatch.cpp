#include <iostream>
#include <locale.h>
#include <filesystem>
#include <sstream>
#include <string>
#include <array>
#include <limits.h>
#include "ArgParser.h"
#include "utils.h"
#include "help.h"

#define RENAME_FLAG "rename"
#define CONVERT_FLAG "convert"
#define RESIZE_FLAG "resize"
#define SCALE_FLAG "scale"
#define HELP_FLAG "help"

#define FOLDER_OPTION "folder"
#define AMOUNT_OPTION "amount"
#define FILTER_OPTION "filter"
#define WIDTH_OPTION "width"
#define HEIGHT_OPTION "height"
#define PREFIX_OPTION "prefix"
#define START_NUMBER_OPTION "startnumber"
#define FROM_OPTION "from"
#define TO_OPTION "to"

#ifdef __unix__
        #include <stdlib.h>
	#define SYSTEM_WARNING "\033[1;31mJUST ONE MODE CAN BE ACTIVE!\nCHECK IF YOU PUT MORE THEN ONE OPTION OR NO OPTION"
	#define FOLDER_EMPTY "\033[1;31mTHE FOLDER ARGUMENT CAN'T BE EMPTY!"
	#define FOLDER_EXISTS "\033[1;31mTHE FOLDER DOESN'T EXISTS"
	#define INVALID_CHARACTERS "\033[1;31mFILTER CANNOT CONTAIN THESE ARGUMENTS: " 
	#define RESET_TERMINAL std::cout << "\033[1;0m \033[0m" << std::endl
	#define WRONG_SIZE "\033[1;31mINVALID VALUE, PLEASE CHECK IF THE PASSED WIDTH AND HEIGHT ARE GREATER THEN ZERO"
	#define FILTER_ERROR "\033[1;31mFILTER OPTION CAN'T BE EMPTY!"
	#define NaN "\033[1;31m VALUE MUST BE A NUMBER"
	#define AMOUNT_WARNING "\033[1;31m AMOUNT MUST BE GREATER THAN ZERO"
	#define START_NUMBER_ERROR "\033[1;31m START NUMBER MUST BE POSITIVE OR ZERO"
	#define INVALID_FORMAT "\033[1;31mINVALID FORMAT OR FORMAT NOT SUPPORTED"
	#define EQUAL_FORMAT_ERROR "\033[1;31mFORMATS ARE EQUAL"

#elif defined(_WIN32) || defined(WIN32)
        #define OS_Windows
        #include <windows.h>
	#define WARNING_TERMINAL system("Color 04")
	#define RESET_TERMINAL system("Color 07")
	#define FOLDER_EMPTY "THE FOLDER ARGUMENT CAN'T BE EMPTY"
	#define FOLDER_EXISTS "THE FOLDER DOESN'T EXIST"
	#define SYSTEM_WARNING "JUST ONE MODE CAN BE ACTIVE!\nCHECK IF YOU PUT MORE THEN ONE OPTION OR NO OPTION"
	#define INVALID_CHARACTERS "FILTER CANNOT CONTAIN THESE ARGUMENTS: "
	#define WRONG_SIZE "INVALID VALUE, PLEASE CHECK IF THE PASSED WIDTH AND HEIGHT ARE GREATER THEN ZERO"
	#define FILTER_ERROR "FILTER OPTION CAN'T BE EMPTY!"
	#define NaN "VALUE MUST BE A NUMBER"
	#define AMOUNT_WARNING "AMOUNT MUST BE GREATER THAN ZERO"
	#define START_NUMBER_ERROR "START NUMBER MUST BE POSITIVE OR ZERO"
	#define INVALID_FORMAT "INVALID FORMAT OR FORMAT NOT SUPPORTED"
	#define EQUAL_FORMAT_ERROR "FORMATS ARE EQUAL"
#endif

const std::string& GetInvalidChars(){
	static const std::string invalidChars = "\\/*?\"<>|:";
	return invalidChars;
}

const bool HasInvalidChars(const std::string& passed_str){
        const bool verifier = passed_str.find_first_of(GetInvalidChars()) != std::string::npos;
	return verifier;

}

const void ThrowExceptionArguments(const ArgParser& argparser){
        // Read the flags that the user puts

	const bool bHelpMode = argparser.GetFlag(HELP_FLAG);
	if (bHelpMode){
		displayHelp();
	}


        const bool bRenameMode = argparser.GetFlag(RENAME_FLAG);
	const bool bConvertMode = argparser.GetFlag(CONVERT_FLAG);
	const bool bResizeMode = argparser.GetFlag(RESIZE_FLAG);
	const bool bScaleMode = argparser.GetFlag(SCALE_FLAG);
	
	// Verify if just one flag is active
	
	if (!(bRenameMode ^ bConvertMode ^ bResizeMode ^ bScaleMode)){ // Not . Exclusive or
		// If more than 1 mode is active, launch exception
		throw std::invalid_argument(SYSTEM_WARNING);

	}

	//Validate passed folder
	
	const std::string folder = argparser.GetOptionAsString(FOLDER_OPTION);
	const bool checkBlanks = check_all_blank(folder);
	if (folder.empty() || checkBlanks == true){
		throw std::invalid_argument(FOLDER_EMPTY);
	}

	if (!std::filesystem::exists(folder)){
		std::stringstream concatenated;
		concatenated << FOLDER_EXISTS << "\nPassed Path: " << folder;
		throw std::invalid_argument(concatenated.str());
		
	}

	//Validate passed filter
	const std::string filter = argparser.GetOptionAsString(FILTER_OPTION);
	bool checkBlankFilter = check_all_blank(filter);
        if ((!filter.empty() && HasInvalidChars(filter)) || checkBlankFilter == false){
		std::stringstream concatenatedStrings;
		concatenatedStrings << INVALID_CHARACTERS << GetInvalidChars();
		throw std::invalid_argument(concatenatedStrings.str());
		

       }

	if (bResizeMode){
		int width = 0;
		int height = 0;

		try{
			width = argparser.GetOptionAsInt(WIDTH_OPTION);
			height = argparser.GetOptionAsInt(HEIGHT_OPTION);
		}catch(std::invalid_argument&){
			throw(NaN);
		}

		// On resize mode, width and height must be > 0
		if (width <= 0 || height <= 0){
			throw std::invalid_argument(WRONG_SIZE);
		}

		if (filter.empty()){
			std::stringstream concatenateFilter;
			concatenateFilter << FILTER_ERROR << " ON RESIZE MODE";
			throw std::invalid_argument(concatenateFilter.str());
		}

	}

	//Validate Scale Mode
	if (bScaleMode){


		float amount = 0.0f;
		try{       
			amount = argparser.GetOptionAsFloat(AMOUNT_OPTION);

		}catch(std::invalid_argument&){
			throw(NaN);
		}

		// Amount must be greater than zero on amount option
		if (amount <= 0){
			throw std::invalid_argument(AMOUNT_WARNING);
		}

		if (filter.empty()){
			std::stringstream concatenateFilterAmount;
			concatenateFilterAmount << FILTER_ERROR << "ON AMOUNT MODE";		
			throw std::invalid_argument(concatenateFilterAmount.str());
		}


	}	
	
	//Validate Rename Mode
	if (bRenameMode){
		int startNumber = argparser.GetOptionAsInt(START_NUMBER_OPTION);
		std::string prefix = argparser.GetOptionAsString(PREFIX_OPTION);

		if (startNumber < 0){
			throw std::invalid_argument(START_NUMBER_ERROR);
		}

		if (prefix.empty() || HasInvalidChars(prefix) || check_all_blank(prefix)){
			std::stringstream concatenatedErrors;
			concatenatedErrors << INVALID_CHARACTERS << GetInvalidChars() << "\n" << "PREFIX CAN'T BE EMPTY OR BLANK!"; 
			throw std::invalid_argument(concatenatedErrors.str());
		}
	}

	//Validate Convert Mode
	if (bConvertMode){
		const std::string from = argparser.GetOptionAsString(FROM_OPTION);
		const std::string to = argparser.GetOptionAsString(TO_OPTION);

		const std::array<std::string, 2> convertOptions = {"jpg", "png"};
		const bool bIsFromValid = std::find(std::begin(convertOptions), std::end(convertOptions), from) != std::end(convertOptions);

		const bool bIsToValid = std::find(std::begin(convertOptions), std::end(convertOptions), to) != std::end(convertOptions);

		if (!bIsFromValid || !bIsToValid){
			throw std::invalid_argument(INVALID_FORMAT);
		}

		if (from == to){
			throw std::invalid_argument(EQUAL_FORMAT_ERROR);
		}

	}

}
	


int main(int argc, const char* argv[]){
	if (argc >= INT_MAX || argc == -2147483648){
		throw std::invalid_argument("For security purposes, this value isn't permitted");
		
	}	
	setlocale(LC_ALL, "");
	setlocale(LC_NUMERIC, "en_US");

	ArgParser argparse;

	argparse.RegisterFlag(RENAME_FLAG);
	argparse.RegisterFlag(CONVERT_FLAG);
	argparse.RegisterFlag(RESIZE_FLAG);
	argparse.RegisterFlag(SCALE_FLAG);
	argparse.RegisterFlag(HELP_FLAG);

	argparse.RegisterOption(FOLDER_OPTION);
	argparse.RegisterOption(AMOUNT_OPTION);
	argparse.RegisterOption(FILTER_OPTION);
	argparse.RegisterOption(WIDTH_OPTION);
	argparse.RegisterOption(HEIGHT_OPTION);
	argparse.RegisterOption(PREFIX_OPTION);
	argparse.RegisterOption(START_NUMBER_OPTION);
	argparse.RegisterOption(FROM_OPTION);
	argparse.RegisterOption(TO_OPTION);


	argparse.Parse(argc, argv);
	
	try{
	    ThrowExceptionArguments(argparse);
	}catch(const std::exception& exception){
               #ifdef __unix
	           std::cerr << exception.what() << std::endl;
	           RESET_TERMINAL;
               #else
		   system("Color 04");
		   std::cerr << exception.what() << std::endl;
	       #endif
	}

	std::cin.get();
	
	
	return 0;
}
