#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_config.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_register.h"



/**********************************************************
 * Name : NVIC_voidEnableInterrupt
 * Arguments : Copy_u8IntNum
 * Return : void
 * Description : ENable interrupt of this position.
 * position number / 32 register => to determine register number.
 * position % 32 => to determine bit number in this register.
 * then write 1 to this bit. assigning the value by -> operator
 * refers to the ISER.
 **********************************************************/
void NVIC_EnableInterrupt(u8 Copy_u8IntNum){
NVIC_reg->ISER[Copy_u8IntNum/32]=(1U<<(Copy_u8IntNum%32));
}

/**********************************************************
 * Name : NVIC_voidDisableInterrupt
 * Arguments : Copy_u8IntNum
 * Return : void
 * Description : disable interrupt of this position.
 * position number / 32 register => to determine register number.
 * position % 32 => to determine bit number in this register.
 * then write 1 to this bit. assigning the value by -> operator
 * refers to the ICER.
 **********************************************************/
void NVIC_DisableInterrupt(u8 Copy_u8IntNum){
NVIC_reg->ICER[Copy_u8IntNum/32]=(1U<<(Copy_u8IntNum%32));
}


/**********************************************************
 * Name : NVIC_voidSetPendingFlag
 * Arguments : A_u8IntPosition
 * Return : void
 * Description : enable interrupt pending of this position.
 * position number / 32 register => to determine register number.
 * position % 32 => to determine bit number in this register.
 * then write 1 to this bit. assigning the value by -> operator
 * refers to the ISPR.
 **********************************************************/
void NVIC_SetPendingFlag(u8 Copy_u8IntNum){
NVIC_reg->ISPR[Copy_u8IntNum/32]=(1U<<(Copy_u8IntNum%32));
}

/**********************************************************
 * Name : NVIC_voidDisablePendingFlag
 * Arguments : A_u8IntPosition
 * Return : void
 * Description : disable interrupt pending of this position.
 * position number / 32 register => to determine register number.
 * position % 32 => to determine bit number in this register.
 * then write 1 to this bit. assigning the value by -> operator
 * refers to the ICPR.
 **********************************************************/
void NVIC_ClearPendingFlag(u8 Copy_u8IntNum){
NVIC_reg->ICPR[Copy_u8IntNum/32]=(1U<<(Copy_u8IntNum%32));
}

/**********************************************************
 * Name : NVIC_voidSetInterruptGroupMode
 * Arguments : (GROUPMODE Enum) Copy_uddGroupMode
 * Return : void
 * Description : select priority grouping levels.
 * to write to this register, VECTKEY must be enabled, otherwise
 * the processor ignores the write.
 * then, select Priority grouping levels (modes):
 * # 16 groups & no subgroup  => write 0b011
 * # 8 groups  & 2 subgroups  => write 0b100
 * # 4 groups  & 4 subgroups  => write 0b101
 * # 2 groups  & 8 subgroups  => write 0b110
 * # no group  & 16 subgroups => write 0b111
 * shifted left by 8 => bit no. 8:10 in AICR
 **********************************************************/
void NVIC_voidSetInterruptGroupMode(NVIC_GROUPMODE_t   Copy_uddGroupMode){
  #define SCB_AIRCR                    *((u32 *)(0xE000ED00))
  SCB_AIRCR=NVIC_VECKEY|(Copy_uddGroupMode<<8);
}

/**********************************************************
 * Name : NVIC_u8GetActiveFlag
 * Arguments : Copy_u8IntNum
 * Return : u8 value of activation bit
 * Description : read active state of this interrupt.
 * position number / 32 register => to determine register number.
 * position % 32 => to determine bit number in this register.
 * then reading this value by -> operator that refers to the IABR.
 **********************************************************/
u8 NVIC_u8GetActiveFlag(u8 Copy_u8IntNum){
 return GET_BIT( NVIC_reg->IABR[Copy_u8IntNum/32],Copy_u8IntNum%32);
}

/**********************************************************
 * Name : NVIC_voidSetInterruptPriority
 * Arguments : Copy_u8IntPosition, Copy_u8GroupLevel, Copy_u8SubGroupLevel,
 * 			   Copy_uddGroupMode.
 * Return : void
 * Description : set interrupt priority value.
 * Group & sub priority depends on priority group mode.
 * # 16 groups & no subgroup  => 0bxxxx
 * # 8 groups  & 2 subgroups  => 0bxxxy
 * # 4 groups  & 4 subgroups  => 0bxxyy
 * # 2 groups  & 8 subgroups  => 0bxyyy
 * # no group  & 16 subgroups => 0byyyy
 * shifted left by 4 => to write in the most significant bits,
 * as The processor implements only bits[7:4] of each field,
 * bits[3:0] read as zero and ignore writes.
 * then, assigning the value by -> operator refers to the IPR.
 **********************************************************/
void NVIC_voidSetInterruptPriority(u8 Copy_u8IntPosition, u8 Copy_u8GroupLevel, u8 Copy_u8SubGroupLevel, NVIC_GROUPMODE_t   Copy_uddGroupMode){
   u8 Local_u8Priority = 0;
   switch (Copy_uddGroupMode)
   {
   case NVIC_GROUPMODE_G16_S0: Local_u8Priority = Copy_u8GroupLevel;break;
   case NVIC_GROUPMODE_G8_S2 : Local_u8Priority = Copy_u8SubGroupLevel|(Copy_u8GroupLevel<<1);break;
   case NVIC_GROUPMODE_G4_S4: Local_u8Priority = Copy_u8SubGroupLevel|(Copy_u8GroupLevel<<2);break;
   case NVIC_GROUPMODE_G2_S8: Local_u8Priority = Copy_u8SubGroupLevel|(Copy_u8GroupLevel<<3);break;
   case NVIC_GROUPMODE_G0_S16: Local_u8Priority = Copy_u8SubGroupLevel; break;
   }
   NVIC_reg->IPR[Copy_u8IntPosition]=Local_u8Priority<<4;
}
