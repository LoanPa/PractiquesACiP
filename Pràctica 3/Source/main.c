/*
 *  102685 Arquitectura de Computadors i Perifèrics 102685
 *	PRÀCTICA Nº 3 CURS 2017/2018 (2020/2021)
 * 
 * INCLUSIÓ DE CODI ASSEMBLADOR DINS DE C I OPERADORS BINARIS
 * 
 * 
 * MADE BY: Ivan Moreno and Loan Panareda Lecomte
 * Last revision: 02/05/2021; 22:26
 * 
 * */
#include "derivative.h" /* include peripheral declarations */

#pragma push // we save the current instuction set code generation 
#pragma arm //we switch code generation to the ARM instruction set

/* 
 *	wait_nop recieves a unsigned long int nop_count
 *	that contains the number of times the function
 *  shall execute the nop operation
 */
void wait_nop(unsigned long int nop_count)
{
	unsigned long int i;
	for(i=0; i < nop_count; i++)
	{	
		asm("NOP");	// asm()allows us to use the arm NOP instruction in C code
	}
}

#pragma pop // we switch back to our initial instruction set code generation

int main(void)
{
	static const unsigned long int ELS_COPS_QUE_ES_VULGUI = 29;
	
	int moviment = -2; // moviment -> 1111...1110
	
	
	moviment |= 1; //  1111...1110 | 0000...0001 -> 1111...1111
	
	unsigned long int i;
	for(i = 0 ; i < ELS_COPS_QUE_ES_VULGUI; i++) // Repetir els cops que es vulgui
	{	   
		moviment <<= 4;
		wait_nop(3);
	}
	
	for(i = 0 ; i < ELS_COPS_QUE_ES_VULGUI; i++) // Repetir els cops que es vulgui
	{	   
		moviment >>= 4;
		wait_nop(3);
	}
	
	return 0;
}

