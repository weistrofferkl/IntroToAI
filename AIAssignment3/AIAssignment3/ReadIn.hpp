//
//  ReadIn.hpp
//  AIAssignment3
//
//  Created by Kendall Weistroffer on 11/4/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

/*
    Header file for the ReadIn.cpp file, contains the image struct, given by Nathan
 */
#ifndef ReadIn_hpp
#define ReadIn_hpp

#include <stdio.h>
#include  "stdint.h"

struct image{
    uint8_t get(int x, int y) const
    { return 255-pixel[x+y*28]; }
    uint8_t pixel[28*28];
    uint8_t value;
};
#endif /* ReadIn_hpp */
