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
    std::cout << GetModeName() << "Mode        : Rename" << std::endl;
    std::cout << GetModeName() << "Folder      : " << GetFolder() << std::endl;
    std::cout << GetModeName() << "Filter      : " << GetFilter() << std::endl;
    std::cout << GetModeName() << "Prefix      : " << m_Prefix << std:: endl;
    std::cout << GetModeName() << "startNumber : " << m_startNumber << std::endl;

    std::vector<std::filesystem::path> filesToRename;
    int numSkippedFiles = 0;

    // Collect all files with the passed filter
    for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(GetFolder())){

        const bool bIsFile = std::filesystem::is_regular_file(entry.path());
        const bool bMatchFilter = GetFilter().empty() || (entry.path().string().find(GetFilter()) != std::string::npos);

        if (bIsFile && bMatchFilter){

            filesToRename.push_back(entry.path());
        }else{
            numSkippedFiles++;
            
        }

        int aux = m_startNumber;

        //Start rename files
        for (const std::filesystem::path& filepath : filesToRename){
            const std::filesystem::path extension = filepath.extension();
            const std::string newFileName = m_Prefix + std::to_string(aux) + extension.string();

            std::filesystem::path newFilePath = filepath;
            newFilePath.replace_filename(newFileName);

            try{
                std::filesystem::rename(filepath, newFilePath);
            }catch(const std::exception& err){
                std::cout << "Error when rename " << filepath << "\n" << err.what() << std::endl;
            }

        }

    }

    std::cout << "Found files  : " << filesToRename.size() << std::endl;
    std::cout << "Ignored Files: " << numSkippedFiles << std::endl;
}