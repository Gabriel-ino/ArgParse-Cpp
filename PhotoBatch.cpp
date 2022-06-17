#include <iostream>
#include <locale.h>
#include "ArgParser.h"

#define RENAME_FLAG "rename"
#define CONVERT_FLAG "convert"
#define RESIZE_FLAG "resize"
#define SCALE_FLAG "scale"

#define FOLDER_OPTION "folder"
#define AMOUNT_OPTION "amount"


#ifdef __unix__
        #include <stdlib.h>
	#define SYSTEM_WARNING "\033[1;31mJUST ONE MODE CAN BE ACTIVE!"
	#define RESET_TERMINAL std::cout << "\033[1;0m \033[0m" << std::endl
#elif defined(_WIN32) || defined(WIN32)
        #define OS_Windows
        #include <windows.h>
	#define WARNING_TERMINAL system("Color 04")
	#define RESET_TERMINAL system("Color 07")
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
		#ifdef __unix__
			throw std::invalid_argument(SYSTEM_WARNING);

		#else
			throw std::invalid_argument("Just one mode can be active");


		#endif	
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
