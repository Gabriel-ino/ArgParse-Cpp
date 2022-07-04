#include "ConvertMode.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

std::string ToString(ConvertMode::Format format){
    switch (format)
    {
    case ConvertMode::Format::JPG:
        /* code */
        return "jpg";
    case ConvertMode::Format::PNG:
        return "png";
    
    default:
        break;
    }
    return "";
}

std::ostream& operator<< (std::ostream& out, ConvertMode::Format format){
    
    out << ToString(format);
    return out;
} 

ConvertMode::ConvertMode(const std::string& filter,
                         const std::string& folder,
                         Format fromFormat,
                         Format toFormat)
        : Mode{filter, folder}
        , m_FromFormat { fromFormat }
        , m_ToFormat   { toFormat }
{}

const std::string& ConvertMode::GetModeName() const{
    static const std::string ConvertModeName {"[Convert]: "};
    return ConvertModeName;
}

void ConvertMode::RunImpl(){
    std::cout << GetModeName() << "Mode          : Convert" << '\n';
    std::cout << GetModeName() << "Folder        : " << GetFolder() << '\n';
    std::cout << GetModeName() << "Filter        : " << GetFilter() << '\n';
    std::cout << GetModeName() << "Origin format : " << m_FromFormat << '\n';
    std::cout << GetModeName() << "Destiny format: " << m_ToFormat << '\n';

    const std::filesystem::path fromExtension{"." + ToString(m_FromFormat)};

    for (const std::filesystem::path& filepath:GetFiles(fromExtension)){
        std::cout << GetModeName() << filepath << '\n';

    }
}

