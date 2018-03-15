//#include "c8051f020.h"                    // SFR declarations
#include <math.h>
#include "Declarations_GPIO_BSE.h"
#include "servo.h"

#define PWM_START 0xDF80                        // starting value for the PWM 

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

unsigned PWM = PWM_START;                      // Number of PCA clocks for 

void init_PCA0(void){
	
		EA=0;
		PWM = 0x80;
		PCA0MD    = 0x03;
		PCA0CPL0  = (0xff & PWM);
		PCA0CPH0  = (0xff & (PWM >> 8));
		PCA0CPM0  = 0x4d;
		EIE1 |= 0x08;
		EA = 1;
		PCA0CN    = 0x40;
}


void PCA_ISR (void) interrupt 9{
		P2^=0x10;
		if (CCF0) {
		CCF0 = 0;
		// clear compare indicator
		if (PWM_OUT) {
				// process rising edge
				PCA0CPL0 = (0xff & PWM);
				// set next match to PWM
				PCA0CPH0 = (0xff & (PWM >> 8));
		} else {
				// process falling edge
				PCA0CPL0 = 0;
				// set next match to zero
				PCA0CPH0 = 0;
		}
		} else if (CCF1) {
		// handle other PCA interrupt
				CCF1 = 0;
		// sources
		} else if (CCF2) {
				CCF2 = 0;
		} else if (CCF3) {
				CCF3 = 0;
		} else if (CCF4) {
				CCF4 = 0;
		} else if (CF) {
				CF = 0;
		}
}
	
void tempo(void){
	long i = 0;
	while(i<(221184/2)) // Temporisation logicielle
	{
		i++; 
	}
}

void MOU(int D){

	float temps;
	int p;
	temps = (10*D + 1500);
	p=(-5.5467)*temps+65600;
	PWM = floor(p);
}

void MOB(int D, int A){
	
	int R=floor(D/2); 
	float temps;
	int p;
	temps = (10*R + 1500);
	p=(-5.5467)*temps+65600;
	PWM = floor(p);
	tempo();
	tempo();	 
	while (R!=-D/2){
		R -= A;
		temps = (10*R + 1500);
		p=(-5.5467)*temps+65600;
		PWM = floor(p);
		tempo();
	}
}

