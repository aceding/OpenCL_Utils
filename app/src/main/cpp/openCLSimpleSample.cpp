//
// Created by aceding on 2017/11/16.
//

#define __CL_ENABLE_EXCEPTIONS

#include "openCLSimpleSample.h"

const char* simple_sample_src[] = {
        "__kernel void add_index(__global int *data){\n"
                "int gid=get_global_id(0);\n"
                "data[gid] += gid;\n"
        "}\n"
};

void simpleSample(){
    LOGI("simpleSample start.");

    //获取platform
    cl_uint num_platforms;
    cl_int err;
    err = clGetPlatformIDs(0, NULL, &num_platforms);
    if(CL_SUCCESS != err) {
        LOGE("can not find any platforms.");
        return;
    } else {
        LOGI("platforms count is: %d.", num_platforms);
    }
    cl_platform_id  *platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
    clGetPlatformIDs(num_platforms, platforms, NULL);

    //获取device
    cl_uint num_devices;
    err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
    if(CL_SUCCESS != err) {
        LOGE("can not find any devices.");
        return;
    } else {
        LOGI("devices count is: %d.", num_devices);
    }
    cl_device_id *devices = (cl_device_id*)malloc(sizeof(cl_device_id) * num_devices);
    clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

    //创建context
    cl_context_properties props[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platforms[0], 0 };
    cl_context context = clCreateContext(props, 1, &devices[0], NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        LOGE("create context error.");
        return;
    }

    //创建command queue
    cl_command_queue  command_queue = clCreateCommandQueue(context, devices[0], 0, &err);
    if(CL_SUCCESS != err) {
        LOGE("create command queue error.");
        return;
    }

    //创建program
    cl_program  program = clCreateProgramWithSource(context, 1, (const char**)&simple_sample_src, NULL, &err);
    if(CL_SUCCESS != err) {
        LOGE("create program error.");
        return;
    }

    //build program
    err = clBuildProgram(program, 1, &devices[0], NULL, NULL, NULL);
    if(CL_SUCCESS != err) {
        LOGE("build program error.");
        return;
    }

    //创建kernel
    cl_kernel kernel = clCreateKernel(program, "add_index", &err);
    if(CL_SUCCESS != err) {
        LOGE("create kernel error.");
        return;
    }

    //创建内存对象
    int inputDataLen = 1024;
    int inputData[inputDataLen];
    for(int i = 0; i < inputDataLen; i++){
        inputData[i] = i;
    }
    cl_mem mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR, inputDataLen * sizeof(int), &inputData[0], &err);
    if(CL_SUCCESS != err) {
        LOGE("create cl_mem buffer error.");
        return;
    }

    //设置kernel 参数
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&mem_obj);
    if(CL_SUCCESS != err) {
        LOGE("set kernel arg error.");
        return;
    }

    //设置work group size
    cl_uint work_dims = 1;
    size_t global_work_offset[] = {0};
    size_t global_work_size[] = {inputDataLen};
    size_t *local_work_size = NULL;
    err = clEnqueueNDRangeKernel(command_queue, kernel, work_dims, global_work_offset, global_work_size, local_work_size, NULL, NULL, NULL);
    if(CL_SUCCESS != err) {
        LOGE("enqueueNDRangeKernel error.");
        return;
    }

    //获取结果
    err =clEnqueueReadBuffer(command_queue, mem_obj, CL_TRUE, 0, inputDataLen * sizeof(int), inputData, 0, NULL, NULL);
    if(CL_SUCCESS != err) {
        LOGE("enqueueReadBuffer error.");
        return;
    }

    //释放资源
    if(NULL != kernel){
        clReleaseKernel(kernel);
    }
    if(NULL != program) {
        clReleaseProgram(program);
    }
    if(NULL != mem_obj) {
        clReleaseMemObject(mem_obj);
    }
    if(NULL != command_queue) {
        clReleaseCommandQueue(command_queue);
    }
    if(NULL != context) {
        clReleaseContext(context);
    }

    //检验结果
    for(int i = 0; i < inputDataLen; i+= 100) {
        LOGI("index %d 's value is %d", i, inputData[i]);
    }
}
