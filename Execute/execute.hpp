#pragma once

#include <iostream>
#include <string>

typedef enum{
    v8      = (1<<0),   // 8v
    v32     = (1<<1),   // 32v
    v64     = (1<<2),   // 64v
    bv      = (1<<3),   // bv
    reg     = (1<<4),   // Rx
    mem     = (1<<5),   // &x
    flag    = (1<<6),   // %x
    indir   = (1<<7),   // *x
    cst     = (1<<8),   // @x
    range   = (1<<9),   // y-x
    label   = (1<<10)   // :x
} parameterType;


const std::string& lllcSuffix(std::string options, unsigned long long line_number);
const std::string& executeParameter(std::string parameter, unsigned long int type, unsigned long long int line_number);