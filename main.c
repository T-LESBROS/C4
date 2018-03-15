#include <c8051f020.h>
#include <math.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#include "LIB_BSE_Config_Globale.h"
#include "Telemetre_ultrasons.h"     
#include "servo.h"
//#include "FO_M1_Structures_COMMANDES_INFORMATIONS_CentraleDeCommande.C"   

extern int telemetre_AV;
extern int telemetre_AR;

void main(void)
{
	EA = 0; //désactivation des interruptions
	Init_Device();
	Config_Timer3(); 
	Init_Telemetre();
	init_PCA0();
	EA = 1; //activation des interruptions 
	
	while(1)
	{
		telemetre_AV = 1;
		tempo();
		MOB(180,15);
	}
}
