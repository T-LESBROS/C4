
# define SYSCLK 22118400
#include "Declarations_GPIO_BSE.h"
#include "Telemetre_ultrasons.h"
//-----------------------------------------------------------------------------------------------------------
// Variables globales
//-----------------------------------------------------------------------------------------------------------
	volatile int cycle_AV;
	volatile int distance_AV;
	volatile	int debut_reception_AV;
	volatile	int fin_reception_AV;
	volatile int reponse_emise_AV;
 	volatile int telemetre_AV;
	volatile int temps_echo_AV;
	
  volatile int	cycle_AR;
	volatile int distance_AR;
	volatile int debut_reception_AR;
	volatile int fin_reception_AR;
	volatile int reponse_emise_AR;
	volatile int telemetre_AR;
	volatile int temps_echo_AR;

// Configuration du Timer3 pour générér une interruption interne toutes les 10.3us
void Config_Timer3(void)
{
	TMR3CN &= ~ 0x03; // Timer 3 uses the system clock divided by 12
	TMR3CN |= 0X04; // Timer3 enabled
	
	TMR3RLL= 0xED;
	TMR3RLH= 0xFF; 
	TMR3L=0xED;
	TMR3H=0xFF;
	
	EIP2 |=0x01; // Haute priorité des interruptions du Timer2
	EIE2 |=0x01;	// Autorisation des interruptions généreés par le flag TF3
}

void Init_Telemetre(void)
{
	
	cycle_AV=0;
	distance_AV=0;
	debut_reception_AV=0;
	fin_reception_AV=0;
	reponse_emise_AV=0;
	
	cycle_AR=0;
	distance_AR=0;
	debut_reception_AR=0;
	fin_reception_AR=0;                                                                                   
	reponse_emise_AR=0;
}

// Génération du signal Trigger de 10.3us
void ISR_Timer3() interrupt 14
{                                                                                                    

	
		if(telemetre_AV == 1) 
		{
			cycle_AV++ ;
			if(cycle_AV == 1)
			{
				P2__0=1; // P2.0 : signal Trigger télémètre AV
			}
			
			else if(cycle_AV == 2)
			{
				P2__0=0; // P2.0 : signal Trigger télémètre AV
			}
			
			
			else if(cycle_AV == 6000){
				cycle_AV = 0;
			}
		
			
			
			
			
			// Mesure distance telemetre AV
			if(P2__1==1) // P2.1 : signal Echo telemetre AV
			{
				if(debut_reception_AV==0)
				{
					debut_reception_AV=1;
				}
				if(fin_reception_AV==0)
				{
					temps_echo_AV++;
				}
			}
			else if(P2__1==0)
			{
				if(debut_reception_AV==1)
				{
					debut_reception_AV=0;
					if(reponse_emise_AV==0)
					{
						distance_AV=(int)(((float)temps_echo_AV*10.3)/58); // Calcul de la distance en cm
						reponse_emise_AV=1;
					}
					fin_reception_AV=1;
				}
			}
		}
		
	if(telemetre_AR == 1)
	{
 		  cycle_AR++ ;
			if(cycle_AR == 1)
			{
				P2__2=1; // P2.2 : signal Trigger télémètre AR
			}
			
			else if(cycle_AR == 2)
			{
				P2__2=0; // P2.2 : signal Trigger télémètre AR
			}
			
			
			else if(cycle_AR == 6000){
				cycle_AR = 0;
			}
	}	
	
	// Mesure distance telemetre AR
			if(P2__3==1) // P2.3 : signal Echo telemetre AR
			{
				if(debut_reception_AR==0)
				{
					debut_reception_AR=1;
				}
				if(fin_reception_AR==0)
				{
					temps_echo_AR++;
				}
			}
			else if(P2__3==0)
			{
				if(debut_reception_AR==1)
				{
					debut_reception_AR=0;
					if(reponse_emise_AR==0)
					{
						distance_AR=(int)(((float)temps_echo_AR*10.3)/58); // Calcul de la distance en cm
						reponse_emise_AR=1;
					}
					fin_reception_AR=1;
				}
			}
		TMR3CN &=0x7F;
}
	
