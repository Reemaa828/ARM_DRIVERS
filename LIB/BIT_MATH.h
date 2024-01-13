#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(num,bit)     num|=1<<bit
#define CLR_BIT(num,bit)     num&=~(1<<bit)
#define TOGGLE_BIT(num,bit)  num^=1<<bit
#define GET_BIT(num,bit)     (num>>bit)&1

#endif
