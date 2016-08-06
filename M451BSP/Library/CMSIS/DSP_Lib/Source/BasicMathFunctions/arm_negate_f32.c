/* ----------------------------------------------------------------------    
* Copyright (C) 2010 ARM Limited. All rights reserved.    
*    
* $Date: 14/06/07 1:56a $Revision: 	V1.1.0  
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_negate_f32.c    
*    
* Description:	Negates floating-point vectors.    
*    
* Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
*  
* Version 1.1.0 2012/02/15 
*    Updated with more optimizations, bug fixes and minor API changes.  
*   
* Version 1.0.10 2011/7/15  
*    Big Endian support added and Merged M0 and M3/M4 Source code.   
*    
* Version 1.0.3 2010/11/29   
*    Re-organized the CMSIS folders and updated documentation.    
*     
* Version 1.0.2 2010/11/11    
*    Documentation updated.     
*    
* Version 1.0.1 2010/10/05     
*    Production release and review comments incorporated.    
*    
* Version 1.0.0 2010/09/20     
*    Production release and review comments incorporated.    
*    
* Version 0.0.7  2010/06/10     
*    Misra-C changes done    
* ---------------------------------------------------------------------------- */

#include "arm_math.h"

/**        
 * @ingroup groupMath        
 */

/**        
 * @defgroup negate Vector Negate        
 *        
 * Negates the elements of a vector.        
 *        
 * <pre>        
 *     pDst[n] = -pSrc[n],   0 <= n < blockSize.        
 * </pre>        
 */

/**        
 * @addtogroup negate        
 * @{        
 */

/**        
 * @brief  Negates the elements of a floating-point vector.        
 * @param[in]  *pSrc points to the input vector        
 * @param[out]  *pDst points to the output vector        
 * @param[in]  blockSize number of samples in the vector        
 * @return none.        
 */

void arm_negate_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize)
{
  uint32_t blkCnt;                               /* loop counter */


#ifndef ARM_MATH_CM0

/* Run the below code for Cortex-M4 and Cortex-M3 */
  float32_t in1, in2, in3, in4;                  /* temporary variables */

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.        
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* read inputs from source */
    in1 = *pSrc;
    in2 = *(pSrc + 1);
    in3 = *(pSrc + 2);
    in4 = *(pSrc + 3);

    /* negate the input */
    in1 = -in1;
    in2 = -in2;
    in3 = -in3;
    in4 = -in4;

    /* store the result to destination */
    *pDst = in1;
    *(pDst + 1) = in2;
    *(pDst + 2) = in3;
    *(pDst + 3) = in4;

    /* update pointers to process next samples */
    pSrc += 4u;
    pDst += 4u;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.        
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

#else

  /* Run the below code for Cortex-M0 */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #ifndef ARM_MATH_CM0 */

  while(blkCnt > 0u)
  {
    /* C = -A */
    /* Negate and then store the results in the destination buffer. */
    *pDst++ = -*pSrc++;

    /* Decrement the loop counter */
    blkCnt--;
  }
}

/**        
 * @} end of negate group        
 */
