
#define oneover255 0.00392156862745f

__kernel void grayKernel(__global uchar4 *srcBuffer,
                                    __global uchar4 *dstBuffer, 
                                    const int width, const int height)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    int centerIndex = y * width + x;
    float4 dstValue4 = (float4)0.0f;

    if(x >= 0 && x <= width && y >= 0 && y <= height){
        float4 srcValue4 = oneover255 * convert_float4(srcBuffer[centerIndex]);
        float dstValue = 0.11 * srcValue4.x + 0.59 * srcValue4.y + 0.30 * srcValue4.z;
        dstValue4 = (float4)dstValue;
        dstValue4.w = 1.0f;

        dstBuffer[centerIndex] = convert_uchar4_sat_rte(255.0f * dstValue4);
    }
}

