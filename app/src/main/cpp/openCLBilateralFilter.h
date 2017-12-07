
#ifndef OPENCLBILATERALFILTER_H
#define OPENCLBILATERALFILTER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>


#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#if defined(__APPLE__) || defined(__MACOSX)
    #include <OpenCL/cl.hpp>
#else
    #include <CL/cl.hpp>
#endif

#include "openCLUtils.h"

void bilateralFilterBitmap (unsigned char* bufIn, unsigned char* bufOut, int* info, std::string programName);

#endif
