
#define sigmaDomain 3.0f
#define sigmaRange  0.2f
#define oneover255 0.00392156862745f
#define filterWidth 2

__kernel void bilateralFilterKernel(__global uchar4 *srcBuffer,
                                    __global uchar4 *dstBuffer, 
                                    const int width, const int height)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    int centerIndex = y * width + x;
    float4  sum4 = (float4)0.0f;
        
	if ( (x >= filterWidth) && (x < (width - filterWidth)) &&     //avoid reading outside of buffer
         (y >= filterWidth) && (y < (height - filterWidth)) )
	{
		float4 centerPixel = oneover255 * convert_float4(srcBuffer[centerIndex]);  
		float normalizeCoeff = 0.0f;
	    
		for (int yy=-filterWidth; yy<=filterWidth; yy++)
		{
			for (int xx=-filterWidth; xx<=filterWidth; xx++)
			{
				int thisIndex = (y+yy) * width + (x+xx); 
				float4 currentPixel = oneover255 * convert_float4(srcBuffer[thisIndex]);
                float domainDistance = fast_distance((float)(xx), (float)(yy));
 				float domainWeight = exp(-0.5f * pow((domainDistance/sigmaDomain),2.0f));
                
				float rangeDistance = fast_distance(currentPixel.xyz, centerPixel.xyz);
				float rangeWeight = exp(-0.5f * pow((rangeDistance/sigmaRange),2.0f));
	            
	            float totalWeight = domainWeight * rangeWeight;
	            normalizeCoeff += totalWeight;
				sum4 += totalWeight * currentPixel;
			}
		}
		sum4 /= normalizeCoeff;
        sum4.w = 1.0f; // set alpha to fully opaque
	}
	dstBuffer[centerIndex] = convert_uchar4_sat_rte(255.0f * sum4);
}

