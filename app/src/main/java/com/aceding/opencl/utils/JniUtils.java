package com.aceding.opencl.utils;


import android.graphics.Bitmap;
import android.os.Build;

public class JniUtils {

    private static final String OCL_MALI_PATH1 = "/system/vendor/lib/egl/libGLES_mali.so";
    private static final String OCL_MALI_PATH2 = "/system/lib/egl/libGLES_mali.so";

    static{
        loadSo();
    }

    public static void loadSo() {
        boolean loadMaliSo = false;
        if (Build.VERSION.SDK_INT >= 24) {
            try {
                System.loadLibrary("hardware");
            } catch (UnsatisfiedLinkError e0) {
                e0.printStackTrace();
            }
        }
        try {
            System.load(OCL_MALI_PATH1);
            loadMaliSo = true;
        } catch (UnsatisfiedLinkError e1) {
            e1.printStackTrace();
            try {
                System.load(OCL_MALI_PATH2);
                loadMaliSo = true;
            } catch (UnsatisfiedLinkError e2) {
                e2.printStackTrace();
                try {
                    System.loadLibrary("GLES_mali");
                    loadMaliSo = true;
                } catch (UnsatisfiedLinkError e3) {
                    e3.printStackTrace();
                }
            }
        }
        if (!loadMaliSo || Build.VERSION.SDK_INT >= 24) {
            try {
                System.loadLibrary("OpenCL");
            } catch (UnsatisfiedLinkError e4) {
                e4.printStackTrace();
            }
        }

        System.loadLibrary("native-lib");
    }

    public static native int bilateralFilterBitmap(Bitmap bmpIn, Bitmap bmpOut, int info[], String programName);
    public static native int grayBitmap(Bitmap bmpIn, Bitmap bmpOut, int info[], String programName);
    public static native void simpleSample();
}
