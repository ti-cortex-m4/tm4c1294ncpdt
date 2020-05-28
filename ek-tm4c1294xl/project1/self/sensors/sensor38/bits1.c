#include "../../main.h"



void left_shift(unsigned int* array)
{
    for (int i=3; i >= 0; i--)
    {
        array[i] = array[i] << 1;

        if (i > 0)
        {
            unsigned int top_bit = (array[i-1] >> 31) & 0x1;
            array[i] = array[i] | top_bit;
        }
    }
}

void right_shift(unsigned int* array)
{
    for (int i=0; i < 4; i++)
    {
        array[i] = array[i] >> 1;

        if (i < 3)
        {
            unsigned int bottom_bit = (array[i+1] & 0x1) << 31;
            array[i] = array[i] | bottom_bit;
        }
    }
}
