#include <iostream>
#include <filesystem>
#include <vector>


#include "RenameMode.h"


RenameMode::RenameMode(const std::string& filter, const std::string& folder, const std::string& prefix, const int startNumber)
	: Mode{ filter, folder }
	, m_Prefix{ prefix }
	, m_startNumber { startNumber }

{

}

const std::string& RenameMode::GetModeName() const{
	static const std::string RenameModeName = "[Rename]: ";
	return RenameModeName;
}

void RenameMode::RunImpl(){
    std::cout << GetModeName() << "Mode        : Rename" << '\n';
    std::cout << GetModeName() << "Folder      : " << GetFolder() << '\n';
    std::cout << GetModeName() << "Filter      : " << GetFilter() << '\n';
    std::cout << GetModeName() << "Prefix      : " << m_Prefix << '\n';
    std::cout << GetModeName() << "startNumber : " << m_startNumber << '\n';

    int aux{m_startNumber};

        //Start rename files
    for (const std::filesystem::path& filepath : GetFiles()){
        const std::filesystem::path extension = filepath.extension();
        const std::string newFileName = m_Prefix + std::to_string(aux) + extension.string();

        std::filesystem::path newFilePath = filepath;
        newFilePath.replace_filename(newFileName);

        try{
            std::filesystem::rename(filepath, newFilePath);
        }catch(const std::exception& err){
            std::cout << "Error when rename " << filepath << '\n' << err.what() << '\n';
        }

    }

}