#ifndef MCAL_NVIC_INTERFACE_H
#define MCAL_NVIC_INTERFACE_H

typedef enum
{
	NVIC_GROUPMODE_G16_S0 = 3,
	NVIC_GROUPMODE_G8_S2     ,
	NVIC_GROUPMODE_G4_S4	 ,
	NVIC_GROUPMODE_G2_S8	 ,
	NVIC_GROUPMODE_G0_S16	 ,
}NVIC_GROUPMODE_t;


void NVIC_EnableInterrupt(u8 Copy_u8IntNum);
void NVIC_DisableInterrupt(u8 Copy_u8IntNum);
void NVIC_SetPendingFlag(u8 Copy_u8IntNum);
void NVIC_ClearPendingFlag(u8 Copy_u8IntNum);
void NVIC_voidSetInterruptGroupMode(NVIC_GROUPMODE_t   Copy_uddGroupMode);
u8 NVIC_u8GetActiveFlag(u8 Copy_u8IntNum);
void NVIC_voidSetInterruptPriority(u8 Copy_u8IntPosition, u8 Copy_u8GroupLevel, u8 Copy_u8SubGroupLevel, NVIC_GROUPMODE_t   Copy_uddGroupMode);
#endif