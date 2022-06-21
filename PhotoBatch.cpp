#include "utils.h"
#include "ArgParser.h"

#include <iostream>
#include <locale.h>
#include <string>
#include <limits.h>

#include "Mode.h"


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
    #define RESET_TERMINAL std::cout << "\033[1;0m \033[0m" << std::endl
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #define RESET_TERMINAL system("Color 07")
#endif

int main(int argc, const char* argv[]){
	if (argc >= INT_MAX || argc == -2147483648){
		throw std::invalid_argument("For security purposes, this value isn't permitted");
		
	}
	
	Mode* mode = new RenameMode{"Filter", "Folder", "Prefix", 1234};
	std::cout << mode->GetModeName() << std::endl;
		
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
	    if(std::unique_ptr<Mode> PhotoBatchMode = CreateMode(argparse))
	        PhotoBatchMode->Run();
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
