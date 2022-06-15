#include <iostream>
#include <locale.h>
#include "ArgParser.h"


int main(int argc, char* argv[]){
	setlocale(LC_ALL, "");
	ArgParser argparse;

	argparse.RegisterFlag("rename");
	argparse.RegisterFlag("convert");
	argparse.RegisterFlag("resize");
	argparse.RegisterFlag("scale");

	for (int i = 0; i < argc; ++i){
		std::cout << argv[i] << std::endl;
	}

	std::cin.get();

	return 0;
}
