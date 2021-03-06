/*  Copyright 2014 Aaron Boxer (boxerab@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#include <string>

#include "ocl_platform.h"
#include "OCLUtil.h"
#include "OCLQueue.h"

class OCLKernel
{
public:
    OCLKernel(KernelInitInfo initInfo);
    virtual ~OCLKernel(void);
    cl_kernel getKernel() {
        return myKernel;
    }
    cl_device_id getDevice() {
        return device;
    }
    tDeviceRC enqueue(int dimension,  size_t global_work_size[3], size_t local_work_size[3]);
    tDeviceRC execute(int dimension, size_t global_work_size[3],  size_t local_work_size[3]);
    tDeviceRC enqueue(int dimension, size_t global_work_offset[3], size_t global_work_size[3], size_t local_work_size[3]);
    tDeviceRC execute(int dimension, size_t global_work_offset[3], size_t global_work_size[3],  size_t local_work_size[3]);
    tDeviceRC finish() {
        return deviceQueue->finish();
    }
protected:
    int CreateAndBuildKernel(std::string openCLFileName, std::string kernelName, std::string buildOptions);
    cl_kernel myKernel;
    cl_command_queue queue;
    cl_program program;
    cl_ulong localMemorySize;
    cl_device_id device;
    cl_context context;
    OCLQueue* deviceQueue;
};

