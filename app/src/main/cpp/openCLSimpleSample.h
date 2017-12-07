//
// Created by aceding on 2017/11/16.
//

#ifndef OPENCLSIMPLESAMPLE_H
#define OPENCLSIMPLESAMPLE_H

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "openCLUtils.h"

void simpleSample ();

#endif