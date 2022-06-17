#ifndef THROWEXCEPTIONARGUMENTS_H_INCLUDED
#define THROWEXCEPTIONARGUMENTS_H_INCLUDED
#include <iostream>
#include <string>
#include <locale.h>
#include "ArgParser.h"

#ifdef __unix__
	#include <stdlib.h>
#elif defined(_WIN32) || defined(WIN32)
	#define OS_Windows
	#include <windows.h>
#endif

RENAME_FLAG;

void ThrowExceptionArguments(const ArgParser& argparser){
	// Verify if just one flag of the PhotoBatch application is active
	
	const bool bRenameMode = argParser
}


#endif	
