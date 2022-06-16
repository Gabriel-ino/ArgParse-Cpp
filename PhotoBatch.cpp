#include <iostream>
#include <locale.h>
#include "ArgParser.h"


int main(int argc, char* argv[]){
	setlocale(LC_ALL, "");
	setlocale(LC_NUMERIC, "en_US");

	ArgParser argparse;

	argparse.RegisterFlag("rename");
	argparse.RegisterFlag("convert");
	argparse.RegisterFlag("resize");
	argparse.RegisterFlag("scale");

	argparse.RegisterOption("folder");
	argparse.RegisterOption("amount");

	argparse.Parse(argc, argv);
	

	std::cout << std::boolalpha << "Rename\t" << argparse.GetFlag("rename") << std::endl;
	std::cout << std::boolalpha << "Convert\t" << argparse.GetFlag("convert") << std::endl;
	std::cout << std::boolalpha << "Resize\t" << argparse.GetFlag("resize") << std::endl;
	std::cout << std::boolalpha << "Scale\t" << argparse.GetFlag("scale") << std::endl;

	std::cout << std::boolalpha << "Folder= " << argparse.GetOptionAsString("folder") << std::endl;
	std::cout << std::boolalpha << "Amount= " << argparse.GetOptionAsInt("amount") << std::endl;

	std::cin.get();

	return 0;
}
