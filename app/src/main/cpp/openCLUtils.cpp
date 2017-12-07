
#include <stdio.h>
#include "openCLUtils.h"

#include <android/bitmap.h>
#include <jni.h>

#include "openCLGray.h"
#include "openCLBilateralFilter.h"
#include "openCLSimpleSample.h"


extern "C" jint
Java_com_aceding_opencl_utils_JniUtils_grayBitmap(JNIEnv* env, jclass clazz, jobject bitmapIn, jobject bitmapOut, jintArray info, jstring programName)
{

    void*	bi;
    void*   bo;

    jint* i = env->GetIntArrayElements(info, NULL);

    AndroidBitmap_lockPixels(env, bitmapIn, &bi);
    AndroidBitmap_lockPixels(env, bitmapOut, &bo);

    const char *programNameTmp = env->GetStringUTFChars(programName, NULL);
    std::string strProgramName(programNameTmp);
    env->ReleaseStringUTFChars(programName, programNameTmp);

    clock_t startTimer1, stopTimer1;
    startTimer1=clock();

    grayBitmap((unsigned char *) bi, (unsigned char *) bo, (int *) i, strProgramName);

    stopTimer1 = clock();
    double elapse = 1000.0* (double)(stopTimer1 - startTimer1)/(double)CLOCKS_PER_SEC;
    ((int *)i)[2] = (int)elapse;
    LOGI("OpenCL code on the GPU took %g ms\n\n", 1000.0* (double)(stopTimer1 - startTimer1)/(double)CLOCKS_PER_SEC) ;


    AndroidBitmap_unlockPixels(env, bitmapIn);
    AndroidBitmap_unlockPixels(env, bitmapOut);
    env->ReleaseIntArrayElements(info, i, 0);

    return 0;
}

extern "C" jint
Java_com_aceding_opencl_utils_JniUtils_bilateralFilterBitmap(JNIEnv* env, jclass clazz, jobject bitmapIn, jobject bitmapOut, jintArray info, jstring programName)
{

    void*	bi;
    void*   bo;

	jint* i = env->GetIntArrayElements(info, NULL);

    const char *programNameTmp = env->GetStringUTFChars(programName, NULL);
    std::string strProgramName(programNameTmp);
    env->ReleaseStringUTFChars(programName, programNameTmp);

    AndroidBitmap_lockPixels(env, bitmapIn, &bi);
    AndroidBitmap_lockPixels(env, bitmapOut, &bo);

	bilateralFilterBitmap((unsigned char *)bi, (unsigned char *)bo, (int *)i, strProgramName);

    AndroidBitmap_unlockPixels(env, bitmapIn);
    AndroidBitmap_unlockPixels(env, bitmapOut);
    env->ReleaseIntArrayElements(info, i, 0);

    return 0;
}

extern "C" void
Java_com_aceding_opencl_utils_JniUtils_simpleSample(JNIEnv* env, jclass clazz)
{
    simpleSample();
}