#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <string.h>
#include <algorithm>
#include <ctype.h>

bool check_all_blank(const std::string& val){
	bool isAllBlank = true;

	for (const char& c : val){
		if (!isblank(c)){
			isAllBlank = false;
		}
	}

	return isAllBlank;
}	

bool check_blank_param(const std::string& flag){
	for (const char& c : flag){
		if (isblank(c)){
			return true;
		}
	}

	return false;
}

#endif
