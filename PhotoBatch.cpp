#include <iostream>
#include <locale.h>
#include "ArgParser.h"

#define RENAME_FLAG "rename"
#define CONVERT_FLAG "convert"
#define RESIZE_FLAG "resize"
#define SCALE_FLAG "scale"

#define FOLDER_OPTION "folder"
#define AMOUNT_OPTION "amount"


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
	

	std::cout << std::boolalpha << "Rename\t" << argparse.GetFlag(RENAME_FLAG) << std::endl;
	std::cout << std::boolalpha << "Convert\t" << argparse.GetFlag(CONVERT_FLAG) << std::endl;
	std::cout << std::boolalpha << "Resize\t" << argparse.GetFlag(RESIZE_FLAG) << std::endl;
	std::cout << std::boolalpha << "Scale\t" << argparse.GetFlag(SCALE_FLAG) << std::endl;

	std::cout << std::boolalpha << "Folder= " << argparse.GetOptionAsString(FOLDER_OPTION) << std::endl;
	std::cout << std::boolalpha << "Amount= " << argparse.GetOptionAsInt(AMOUNT_OPTION) << std::endl;

	std::cin.get();

	return 0;
}
