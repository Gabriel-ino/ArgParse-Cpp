#ifndef ARGPARSER_H_INCLUDED
#define ARGPARSER_H_INCLUDED

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <map>
#include <algorithm>
#include "utils.h"

//Class used to read the arguments passed by the user on the terminal
/* E.g.: ArgParser argparser;
 * argparser.RegisterFlag("Rename");
 * argparser.Parse(argc, argv);
 * argparser.GetFlag("Rename");
 *
 * 
 * */
class ArgParser{
	public:
		// Register flag during parser
		void RegisterFlag(const std::string& flag){
			bool isAllBlank = check_all_blank(flag);

			if (!flag.empty() || isAllBlank == false){
				m_Flags[flag] = false;
			}

		}
		
		// Register option during the parser
		void RegisterOption(const std::string& option){

			bool isAllBlank = check_all_blank(option);

			if (!option.empty() || isAllBlank == false){
				m_Options[option] = "";

			}
		
		}

		
		// Get flag's value during parse
		bool GetFlag(const std::string& flag){
			bool isAllBlank = check_all_blank(flag);

			if (!flag.empty() || isAllBlank == false){
				auto flagIterator = m_Flags.find(flag);

				if (flagIterator != std::end(m_Flags)){
					return flagIterator->second;
				}
			}

			return false;}
		


		// Get option's value as float type
		float GetOptionAsFloat(const std::string& option) const{
			const std::string& optionValue = GetOption(option);
			if (!optionValue.empty()){
				return std::stof(optionValue);
			}
			return -1;
			
		}

		int GetOptionAsInt(const std::string& option) const{
			const std::string& optionValue = GetOption(option);
			bool isAllBlank = check_all_blank(optionValue);
			if (!optionValue.empty()){
				return std::stoi(optionValue);
			}

			return 0;
		
		}

		std::string GetOptionAsString(const std::string& option) const {return GetOption(option);}
		
		// Parse the arguments list on argv
		void Parse(int argc, char* argv[]){
			if (argc > 1){
				for (int index = 1; index < argc; ++index){
					std::string arg = argv[index];
					std::for_each(arg.begin(), arg.end(), [](char & c){
							c = ::tolower(c);
							}); // Putting all characters to lowercase

					// The arguments must have at least 3 characters;
					// The 2 first -- and at least a third character;
					if (arg.length() >= 3){
						if (arg[0] == '-' && arg[1] == '-'){
							//Now, let's remove the "--"
							arg = arg.substr(2);
							
							//Now let's remove any spaces in the begin or in the end of the argument
							std::remove(arg.begin(), arg.end(), ' ');

							// Now let's check if the = characters is in the string
							if (arg.find_first_of('=') != std::string::npos){
								// It's a option!
								const size_t equalPos = arg.find('=');
								if (equalPos != std::string::npos){
									std::string optionName = arg.substr(0, equalPos);
									std::string optionValue = arg.substr(equalPos + 1);
									auto optionIterator = m_Options.find(optionName);
									if (optionIterator != std::end(m_Options)){
											optionIterator->second = optionValue;
									}

								}
								

							}else{
								// It's a flag!
								auto flagIterator = m_Flags.find(arg); // The iterator is a pointer equivalent
								if (flagIterator != std::end(m_Flags)){
									//Found the flag!
									flagIterator->second = true;
								}
							}

						
						}
					}
				}
			}

		}
	

	private:

		std::map<std::string, bool> m_Flags;
		std::map<std::string, std::string> m_Options;

		// Get option's value during the parser
                const std::string& GetOption(const std::string& option) const{
			bool isAllBlank = check_all_blank(option);
                        if (!option.empty() || isAllBlank == false){
                                auto optionIterator = m_Options.find(option);

                                if (optionIterator != std::end(m_Options)){
                                        return optionIterator->second;
                                }
                        }

                        static std::string EmptyOption = "";
                        return EmptyOption;
                }


};

#endif
