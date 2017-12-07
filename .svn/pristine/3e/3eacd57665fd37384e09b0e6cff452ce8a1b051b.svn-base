package com.aceding.opencl.utils;

import android.content.Context;
import android.content.res.AssetManager;
import android.text.TextUtils;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

public class FileUtils {

    public static boolean copyAssetToFile(Context context, String assetFileName, String dstFileName) {
        if(TextUtils.isEmpty(dstFileName)) {
            return false;
        }
        File dstFile = new File(dstFileName);
        return copyAssetToFile(context, assetFileName, dstFile);
    }

    public static boolean copyAssetToFile(Context context, String assetFileName, File dstFile) {
        BufferedInputStream originFis = null;
        OutputStream out = null;
        try {
            Log.i("opencl", dstFile.getAbsolutePath());
            out = new FileOutputStream(dstFile);
            AssetManager am = context.getAssets();
            originFis = new BufferedInputStream(am.open(assetFileName));
            byte[] originBuffer = new byte[1024 * 8];
            int originLength = 0;
            while ((originLength = originFis.read(originBuffer)) != -1) {
                out.write(originBuffer, 0, originLength);
            }
            return true;
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (originFis != null) {
                try {
                    originFis.close();
                } catch (IOException e) {
                }
            }
            if (out != null) {
                try {
                    out.close();
                } catch (IOException e) {
                }
            }
        }
        return false;
    }
}
