#ifndef HELP_H_INCLUDED
#define HELP_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

void displayHelp(){
	std::ifstream helpFile;
	helpFile.exceptions(std::ifstream::badbit);
	try{
		helpFile.open("help.txt");
		if (helpFile.fail()) throw std::invalid_argument("help.txt");
		if (helpFile.is_open()){
			std::string line;
			while (std::getline(helpFile, line)){
				std::cout << line << std::endl;
			}
			helpFile.close();
			std::cin.get();
			exit(EXIT_SUCCESS);
		}
	}catch (const std::exception& err){
		std::cout << "Oooops, something went wrong, check if the file exists" << std::endl;
		std::cout << "File typed: " << err.what() << std::endl; 
		helpFile.close();
		exit(EXIT_FAILURE);
	}

}


#endif
