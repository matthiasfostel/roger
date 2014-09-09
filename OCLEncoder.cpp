/*  Copyright 2014 Aaron Boxer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once

#include "OCLEncoder.h"
#include "OCLDWTForward.cpp"
#include "OCLUtil.h"
#include "OCLMemoryManager.cpp"




template<typename T> OCLEncoder<T>::OCLEncoder(ocl_args_d_t* ocl, bool isLossy) :
	_ocl(ocl), 
	lossy(isLossy),
	memoryManager(new OCLMemoryManager<T>(ocl)),
	dwt(new OCLDWTForward<T>(KernelInitInfoBase(_ocl->commandQueue,  "-I . -D WIN_SIZE_X=8 -D WIN_SIZE_Y=128"), memoryManager))
{

}


template<typename T> OCLEncoder<T>::~OCLEncoder(){
	if (dwt)
		delete dwt;
}

template<typename T> void OCLEncoder<T>::run(std::vector<T*> components,int w,int h, int levels){
	memoryManager->init(components,w,h,lossy,levels);
	dwt->run(lossy, w,h, 8,128,1,levels);
}

template<typename T> void OCLEncoder<T>::finish(void){

	clFinish(_ocl->commandQueue);
}

template<typename T>  tDeviceRC OCLEncoder<T>::mapOutput(void** mappedPtr){
	return memoryManager->mapImage(*memoryManager->getDwtOut(), mappedPtr);
}
template<typename T> tDeviceRC OCLEncoder<T>::unmapOutput(void* mappedPtr){

	return memoryManager->unmapImage(*memoryManager->getDwtOut(), mappedPtr);
}

