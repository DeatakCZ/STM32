#ifndef FIR_H_
#define FIR_H_

#include "stdint.h"

#define FILTER_DATA_TYPE    uint16_t

#define FILTERS_NUM         1

#define SUMMING_BUFFER_LEN  5

typedef struct
{
    uint16_t Filter_Order;
    uint16_t Buffer_Index;
    FILTER_DATA_TYPE* Data_Buffer;
    float* Filter_Coeffecients;
}FIR_Filter_cfg;

void AVG_FIR_LPF(FILTER_DATA_TYPE IN, FILTER_DATA_TYPE* OUT, FIR_Filter_cfg* FILTER_OBJ);

void SUM_BUFFER(FILTER_DATA_TYPE IN, FILTER_DATA_TYPE* SUM, FIR_Filter_cfg* FILTER_OBJ);

#endif