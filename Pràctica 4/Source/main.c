/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */



int main(void)
{

	// 1) Activar el clock gating pel PORTB
	SIM_BASE_PTR->SCGC5 |= 0x400u;
	
	// 2) 3) Inicialitzar el touch
	
	SIM_SCGC5 |= 0x20u ;
	
	TSI0_GENCS |= ( TSI_GENCS_MODE(0)
	 | TSI_GENCS_REFCHRG(4) // Reference charge 4 uA
	 | TSI_GENCS_DVOLT(0) // Voltage rails 
	 | TSI_GENCS_EXTCHRG(7) // External osc charge
	 | TSI_GENCS_PS(4) // Prescalar divide by 4
	 | TSI_GENCS_NSCN(11) // Scans per electrode
	 | TSI_GENCS_STPE_MASK ); // Enable in STOP mode 
	
	// 4 MUX
	
	PORTB_BASE_PTR->PCR[16] = 0 ;
	PORTB_BASE_PTR->PCR[17] = 0 ;
	
	// 5 LED
	
	PORTB_BASE_PTR->PCR[18] |= (1<<8) ;
	PORTB_BASE_PTR->PCR[19] |= (1<<8) ;

	// 6 SORTIDA
	
	PTB_BASE_PTR->PDDR |= (3<<18);
	
	// 7 CAPTURA TEMPS
	TSI0_BASE_PTR->GENCS |= (1<<7);
	TSI0_BASE_PTR->DATA  |= ( (1<<22)|(9<<28) );
	
	//Esperar a que acabe
	uint16_t base;
	while(!(TSI0_BASE_PTR->GENCS & 4))
	{
		;
	}
	
	base=TSI0_BASE_PTR->DATA & 0xFFFF;
	//(void)base;
	
	TSI0_BASE_PTR->GENCS |= 4;
	
	// 8)
	
	while(1)
	{
		TSI0_BASE_PTR->DATA  |= ( (1<<22)|(9<<28) );
		
		//Esperar a que acabe
		uint16_t new;
		while(!(TSI0_BASE_PTR->GENCS & 4))
		{
			;
		}
		
		new=TSI0_BASE_PTR->DATA & 0xFFFF;
	
		// reset flag
		TSI0_BASE_PTR->GENCS |= 4;
		// green LED -> 18
	// red LED -> 19
		if((new - base) > 2)
		{
			PTB_BASE_PTR->PDOR = 1 << 18;
			//green LED on 
			// red LED off
			
		}
		else
		{

			PTB_BASE_PTR->PDOR = 1 << 19;

					//green LED off
					// red LED on
		}
		
	}
	
	
	
	
	return 0;
}
