/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */

static const short int GREEN = 18;
static const short int RED = 19;



/**
 * This function sets 
 * @param set_value indicates which value shall the LED be set to
 * @param colour indicates the LED to 
 **/
void Set_LED(short int set_value, short int colour)
{
	if(set_value == 1)
		PTB_BASE_PTR->PDOR = 1 << colour;
	else
		PTB_BASE_PTR->PDOR &= ~1 << colour;
}

void Change_LED_state(colour)
{
	PTB_BASE_PTR->PDOR = 1 << colour;
}

/**
 * This function waits until the scan of the touch sensor is completed
 **/
void Wait_touch_scan()
{
	while(!(TSI0_BASE_PTR->GENCS & 4))
			{
				;
			}
}


/**
 * This function resets the end of scan flag related to the touch sensor
 **/
void Reset_EOSF()
{
	TSI0_BASE_PTR->GENCS |= 4;	
}

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
	
	//TODO: posar els dos leds a 0
	Set_LED(1, GREEN);
	Set_LED(1, RED);
	PTB_BASE_PTR->PDDR |= (3<<18);
	
	// 7 CAPTURA TEMPS
	TSI0_BASE_PTR->GENCS |= (1<<7);
	TSI0_BASE_PTR->DATA  |= ( (1<<22)|(9<<28) );
	


	uint16_t base_scan_time;
	uint16_t new_scan_time;
	uint16_t delta_scan_time;

	
	Wait_touch_scan();
	
	//This measurement will serve as the reference to detect changes in the touch sensor
	base_scan_time = TSI0_BASE_PTR->DATA & 0xFFFF;
	
	
	// reset end of scan flag
	Reset_EOSF();
	
	// 8)
	
	
	
	while(1)
	{
		TSI0_BASE_PTR->DATA  |= ( (1<<22)|(9<<28) );
		
		
		
		//Esperar a que acabe
		Wait_touch_scan();
		
		new_scan_time=TSI0_BASE_PTR->DATA & 0xFFFF;
	
		// reset end of scan flag
		Reset_EOSF();
		
		delta_scan_time = new_scan_time - base_scan_time;
		
		if(delta_scan_time > 2)
		{	
			// GREEN LED on
			//Set_LED(1, GREEN);	
			Change_LED_state(GREEN);
			// RED LED off
			//Set_LED(0, RED);
		}
		else
		{
			// red LED on		
			//Set_LED(1, RED);
			Change_LED_state(RED);
			//green LED off
			//Set_LED(0, GREEN);					
		}
		
	}
	
	
	
	
	return 0;
}
