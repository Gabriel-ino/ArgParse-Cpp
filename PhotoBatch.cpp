#include <iostream>
#include <locale.h>
#include <filesystem>
#include <sstream>
#include <string>

#include "ArgParser.h"
#include "utils.h"

#define RENAME_FLAG "rename"
#define CONVERT_FLAG "convert"
#define RESIZE_FLAG "resize"
#define SCALE_FLAG "scale"

#define FOLDER_OPTION "folder"
#define AMOUNT_OPTION "amount"
#define FILTER_OPTION "filter"
#define WIDTH_OPTION "width"
#define HEIGHT_OPTION "height"


#ifdef __unix__
        #include <stdlib.h>
	#define SYSTEM_WARNING "\033[1;31mJUST ONE MODE CAN BE ACTIVE!\nCHECK IF YOU PUT MORE THEN ONE OPTION OR NO OPTION"
	#define FOLDER_EMPTY "\033[1;31mTHE FOLDER ARGUMENT CAN'T BE EMPTY!"
	#define FOLDER_EXISTS "\033[1;31mTHE FOLDER DOESN'T EXISTS"
	#define INVALID_CHARACTERS "\033[1;31mFILTER CANNOT CONTAIN THESE ARGUMENTS: " 
	#define RESET_TERMINAL std::cout << "\033[1;0m \033[0m" << std::endl
	#define WRONG_SIZE "\033[1;31mINVALID VALUE, PLEASE CHECK IF THE PASSED WIDTH AND HEIGHT ARE GREATER THEN ZERO"
	#define RESIZE_FILTER_ERROR "\033[1;31m ON RESIZE MODE, FILTER OPTION CAN'T BE EMPTY!"
	#define NaN "\033[1;31m VALUE MUST BE A NUMBER"

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
	#define RESIZE_FILTER_ERROR "ON RESIZE MODE, FILTER OPTION CAN'T BE EMPTY!"
	#define NaN "VALUE MUST BE A NUMBER"
#endif

const void ThrowExceptionArguments(const ArgParser& argparser){
        // Read the flags that the user puts

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
        if (!filter.empty() || checkBlankFilter == false){
		const std::string invalidChars = "\\/*?\"<>|:";
		if (filter.find_first_of(invalidChars) != std::string::npos){
			std::stringstream concatenatedStrings;
			concatenatedStrings << INVALID_CHARACTERS << invalidChars;
			throw std::invalid_argument(concatenatedStrings.str());
		}

       }

	if (bResizeMode){
		int width = 0;
		int height = 0;

		try{
			width = argparser.GetOptionAsInt(WIDTH_OPTION);
			height = argparser.GetOptionAsInt(HEIGHT_OPTION);
		}catch(std::invalid_argument& err){
			throw(NaN);
		}

		// On resize mode, width and height must be > 0
		if (width <= 0 || height <= 0){
			throw std::invalid_argument(WRONG_SIZE);
		}

		if (filter.empty()){
			throw std::invalid_argument(RESIZE_FILTER_ERROR);
		}

	}	
	
}
	


int main(int argc, char* argv[]){
	setlocale(LC_ALL, "");
	setlocale(LC_NUMERIC, "en_US");

	ArgParser argparse;

	argparse.RegisterFlag(RENAME_FLAG);
	argparse.RegisterFlag(CONVERT_FLAG);
	argparse.RegisterFlag(RESIZE_FLAG);
	argparse.RegisterFlag(SCALE_FLAG);

	argparse.RegisterOption(FOLDER_OPTION);
	argparse.RegisterOption(AMOUNT_OPTION);
	argparse.RegisterOption(FILTER_OPTION);
	argparse.RegisterOption(WIDTH_OPTION);
	argparse.RegisterOption(HEIGHT_OPTION);

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
