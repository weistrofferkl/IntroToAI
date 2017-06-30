//
//  ReadIn.cpp
//  AIAssignment3
//
//  Created by Kendall Weistroffer on 11/4/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

/*
    Code used to read in the data, provided by Nathan
 */
#include "ReadIn.hpp"
#include "stdint.h"
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

//std::string basePath = "/Users/Lockwood/Desktop/Fall Quarter 2016/AI/AIAssignment3";

class ReadIn{
    
public:
void SwapEndian(uint32_t &val)
{
    val = ((val & 0xFF) << 24) | ((val & 0xFF00) << 8) | ((val >> 8) & 0xFF00) |
    ((val >> 24) & 0xFF);
}
void LoadData(std::vector<image> &images, const char *imageFile, const char *labelFile){
    
    uint32_t dataCount;
    std::string path = ""; // = basePath;
    path += imageFile;
    FILE *f = fopen(path.c_str(), "r");
    if(f == 0){
        std::cout<< "Hello there humans" << std::endl;
    }
    uint32_t tmp;
    fread(&tmp, sizeof(tmp), 1, f);
    SwapEndian(tmp);
    assert(tmp == 0x00000803); // magic number
    printf("Read: 0x%X\n", tmp);
    fread(&dataCount, sizeof(dataCount), 1, f);
    SwapEndian(dataCount);
    printf("Read: 0x%X\n", tmp); // num entries
    fread(&tmp, sizeof(tmp), 1, f);
    SwapEndian(tmp);
    assert(tmp == 28);
    printf("Read: 0x%X\n", tmp); // image size
    fread(&tmp, sizeof(tmp), 1, f);
    SwapEndian(tmp);
    assert(tmp == 28);
    printf("Read: 0x%X\n", tmp); // image size
    image i;
    for (int x = 0; x < dataCount; x++) // read image data
    {
        size_t read = fread(i.pixel, sizeof(uint8_t), 28*28, f);
        assert(read == 28*28);
        images.push_back(i);
    }
   // std::cout <<"Images size: " << images.size() << std::endl;
    fclose(f);
    path =""; //basePath;
    if (path.back() != '/' && path.size() > 1)
        path.push_back('/');
    path += labelFile;
    fopen(path.c_str(), "r");
    fread(&tmp, sizeof(tmp), 1, f);
    SwapEndian(tmp);
    assert(tmp == 0x00000801); // magic number
    printf("Read: 0x%X\n", tmp);
    fread(&tmp, sizeof(tmp), 1, f);
    SwapEndian(tmp);
    assert(tmp == dataCount); // num instances
    printf("Read: 0x%X\n", tmp);
    for (int x = 0; x < dataCount; x++) // labels
        
    {
        size_t read = fread(&images[x].value, sizeof(uint8_t), 1, f);
        assert(read == 1);
    }
    fclose(f);
}

};
