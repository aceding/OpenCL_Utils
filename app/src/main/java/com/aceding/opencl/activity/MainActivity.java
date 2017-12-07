package com.aceding.opencl.activity;

import java.io.File;

import android.app.Activity;

import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.os.Bundle;

import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.aceding.opencl.R;
import com.aceding.opencl.utils.FileUtils;
import com.aceding.opencl.utils.JniUtils;

public class MainActivity extends Activity {
    protected static final String TAG = "OpenCL";

    private final int info[] = new int[3]; // Width, Height, Execution time (ms)

    private Bitmap bmpOrig, bmpBilateralFilter, bmpGray;
    private ImageView imageView, imageViewNew;
    private TextView textView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imageView = (ImageView) findViewById(R.id.image_orig);
        imageViewNew = (ImageView) findViewById(R.id.image_new);
        textView = (TextView) findViewById(R.id.resultText);

        FileUtils.copyAssetToFile(this, "bilateralKernel.cl", new File(getDir("execdir",MODE_PRIVATE), "bilateralKernel.cl"));
        FileUtils.copyAssetToFile(this, "grayKernel.cl", new File(getDir("execdir",MODE_PRIVATE), "grayKernel.cl"));

        bmpOrig = BitmapFactory.decodeResource(this.getResources(), R.drawable.data);
        info[0] = bmpOrig.getWidth();
        info[1] = bmpOrig.getHeight();

        bmpBilateralFilter = Bitmap.createBitmap(info[0], info[1], Config.ARGB_8888);
        bmpGray = Bitmap.createBitmap(info[0], info[1], Config.ARGB_8888);
        textView.setText("Original");
        imageView.setImageBitmap(bmpOrig);
    }

    public void showGrayImage(View v) {
        JniUtils.grayBitmap(bmpOrig, bmpGray, info, "grayKernel.cl");
        textView.setText("Gray, OpenCL, Processing time is " + info[2] + " ms");
        imageViewNew.setImageBitmap(bmpGray);
    }

    public void showBilateralFilterImage(View v) {
        JniUtils.bilateralFilterBitmap(bmpOrig, bmpBilateralFilter, info, "bilateralKernel.cl");
        textView.setText("Bilateral Filter, OpenCL, Processing time is " + info[2] + " ms");
        imageViewNew.setImageBitmap(bmpBilateralFilter);
    }

    public void runSimpleSample(View v){
        textView.setText("simple sample.");
        JniUtils.simpleSample();
    }
}
