#include "xml.h"
#include "tinyxml2.h"
#include "base64.h"
#include <iostream>
#include <string>
#include <fstream>
#pragma once

namespace base64{
    template <typename T>
    void serialize_base64(const T& value, const std::string& filename);

    template <typename T>
    void deserialize_base64(T& value, const std::string& filename);
} // namespace base64

template <typename T>
void base64::serialize_base64(const T& value, const std::string& filename){
    XML::xmlSerialBase base;
    base.serialize_xml(value, filename);

    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()){
        std::cout << "open file " << filename << " failed" << std::endl;
        return;
    }
    std::string str = base64::base64_encode(reinterpret_cast<const unsigned char*>(&value), sizeof(T));
    ofs << str;
    ofs.close();
}