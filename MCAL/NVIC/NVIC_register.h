#ifndef MCAL_NVIC_REGISTER_H
#define MCAL_NVIC_REGISTER_H

#define NVIC_reg                                         ((NVIC_t *)0xE000E100)

typedef struct{
    u32 ISER[8];
	u32 RESERVED0[24];
	u32 ICER[8];
	u32 RESERVED1[24];
	u32 ISPR[8];
	u32 RESERVED2[24];
	u32 ICPR[8];
	u32 RESERVED3[24];
	u32 IABR[8];
	u32 RESERVED4[56];
	u32 IPR[60];
	u32 RESERVED5[580];
	u32 STIP;
}NVIC_t;


#endif