
// Ajout des en-têtes
#include "LIB_BSE_Config_Globale.h"
#include "Declarations_GPIO_BSE.h"



//-------------------------------------------------------------------------
// Fonctions
//-------------------------------------------------------------------------


//Désactivation du Watchdog  
void Init_watchdog(void)
{
	 Reset_Sources_Devices();
	 WDTCN = 0xde;   				 
	 WDTCN = 0xad;
	 
}

// Configuration de l'horloge
void Oscillator_Init(void)
{
	int i=0;
	OSCXCN = 0x67; //Choix de l'oscillateur à quartz, f>6.7 MHz
	for(i=0;i<3000;i++); //Attente de 1ms pour l'initialisation
	while((OSCXCN & 0x80) == 0); //Attente de la stabilisation de l'oscillateur à quartz
	OSCICN = 0x0C; // Basculement sur l'oscillateur extrerne
}

// Affectation des broches aux périphériques internes 
void Port_IO_Init(void)
{

	//Configurations ports P2.0 à P2.3
	
	XBR0 |= 0xFF;
	XBR1 |= 0x0F;
	XBR2 |= 0x44; // Activation crossabr
	
	P2MDOUT &= ~ 0x0A;// P2.1 et P2.3 en entrée
	P2MDOUT |= 0x15;// P2.0 et P2.2 en sortie
	//P2MDOUT = 0xff;
	
	P2=0x1F;

}

//Fonction de reset des sources et du Watchdog
void Reset_Sources_Devices(void){
	RSTSRC=0x08;
}


// Initialisation globale du 8051F020
void Init_Device(void)
{	
	
	Init_watchdog();
	Oscillator_Init();
	Port_IO_Init();
	
}

