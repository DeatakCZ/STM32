#include "FIR.h"
#include "FIR_cfg.h"

void AVG_FIR_LPF(FILTER_DATA_TYPE IN, FILTER_DATA_TYPE* OUT, FIR_Filter_cfg* FILTER_OBJ)
{
    int32_t SUM = 0;
    uint16_t i = 0;

    //Push the input into the buffer
    FILTER_OBJ->Data_Buffer[FILTER_OBJ->Buffer_Index] = IN;
    FILTER_OBJ->Buffer_Index++;
    if(FILTER_OBJ->Buffer_Index == FILTER_OBJ->Filter_Order+1)
    {
        FILTER_OBJ->Buffer_Index = 0;
    }

    //Calculate the Average for the data in buffer
    for(i = 0 ; i < FILTER_OBJ->Filter_Order+1 ; i++)
    {
        SUM += FILTER_OBJ->Data_Buffer[i];
    }
    *OUT = SUM / (FILTER_OBJ->Filter_Order+1);
}

void SUM_BUFFER(FILTER_DATA_TYPE IN, FILTER_DATA_TYPE* SUM, FIR_Filter_cfg* FILTER_OBJ)
{
    int32_t temp_sum = 0;
    uint16_t i = 0;

    //Push input to the buffer
    FILTER_OBJ->Data_Buffer[FILTER_OBJ->Buffer_Index] = IN;
    FILTER_OBJ->Buffer_Index++;
    if(FILTER_OBJ->Buffer_Index == SUMMING_BUFFER_LEN)
    {
        FILTER_OBJ->Buffer_Index = 0;
    }

    //Calculate the Accumulated Sum for the buffer
    for(i = 0 ; i < SUMMING_BUFFER_LEN ; i++)
    {
        temp_sum += FILTER_OBJ->Data_Buffer[i];
    }
    *SUM = (uint16_t)temp_sum;
}