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


#ifdef __unix__
        #include <stdlib.h>
	#define SYSTEM_WARNING "\033[1;31mJUST ONE MODE CAN BE ACTIVE!\nCHECK IF YOU PUT MORE THEN ONE OPTION OR NO OPTION"
	#define FOLDER_EMPTY "\033[1;31mTHE FOLDER ARGUMENT CAN'T BE EMPTY!"
	#define FOLDER_EXISTS "\033[1;31mTHE FOLDER DOESN'T EXISTS"
	#define INVALID_CHARACTERS "\033[1;31mFILTER CANNOT CONTAIN THESE ARGUMENTS: " 
	#define RESET_TERMINAL std::cout << "\033[1;0m \033[0m" << std::endl
#elif defined(_WIN32) || defined(WIN32)
        #define OS_Windows
        #include <windows.h>
	#define WARNING_TERMINAL system("Color 04")
	#define RESET_TERMINAL system("Color 07")
	#define FOLDER_EMPTY "THE FOLDER ARGUMENT CAN'T BE EMPTY"
	#define FOLDER_EXISTS "THE FOLDER DOESN'T EXIST"
	#define SYSTEM_WARNING "JUST ONE MODE CAN BE ACTIVE!\nCHECK IF YOU PUT MORE THEN ONE OPTION OR NO OPTION"
	#define INVALID_CHARACTERS "FILTER CANNOT CONTAIN THESE ARGUMENTS: "
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
		std::cout << "Here" << std::endl;
		throw std::invalid_argument(SYSTEM_WARNING);

	}

	//Validate passed folder
	
	const std::string folder = argparser.GetOptionAsString(FOLDER_OPTION);
	const bool checkBlanks = check_all_blank(folder);
	if (folder.empty() || checkBlanks == true){
		throw std::invalid_argument(FOLDER_EMPTY);
	}

	if (!std::filesystem::exists(folder)){
		throw std::invalid_argument(FOLDER_EXISTS);
		
	}

	//Validade passed filter
	const std::string filter = argparser.GetOptionAsString(FILTER_OPTION);
	bool checkBlankFilter = check_all_blank(filter);
       if (!filter.empty() || checkBlankFilter == false){
		const std::string invalidChars = "\\/*?\"<>|";
		if (filter.find_first_of(invalidChars) != std::string::npos){
			std::stringstream concatenatedStrings;
			concatenatedStrings << INVALID_CHARACTERS << invalidChars;
			throw std::invalid_argument(concatenatedStrings.str());
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
