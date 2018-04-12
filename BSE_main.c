/* 
* Fichier: BSE_main.c
* Auteurs: DEMUYNCK
* Date dernière modif: 11/12/2017
* Objectif: Main
*/
#include "F0_M1_Struct_Def.h"
#include "F0_M2_Struct_Def.h"


	
// Ajout des en-têtes
#include <c8051f020.h>                    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include <string.h>

#include "LIB_BSE_Config_Globale.h"
#include "LIB_BSE_UART.h"


#include "UART0_RingBuffer_lib.h"
#include "UART1_RingBuffer_lib.h"

#include "FCT_Dec_PC_COM.h"


sbit BP = P3^7;

//-------------------------------------------------------------------------
// Variables globales
//-------------------------------------------------------------------------
# define SYSCLK 22118400 
//#define BAUDRATE  115200L          // Baud rate of UART in bps
                                   // Le caractère 'L' force l'évaluation de BAUDRATE en entier long
//-------------------------------------------------------------------------
// Fonctions
//-------------------------------------------------------------------------



void main(void)
{
	struct COMMANDES* CentralOut;
	struct COMMANDES_SERIALIZER SerialIn;
	char  c;
	
//	CentralOut.Etat_Mouvement = Avanceazqér;
	EA = 0; //désactivation des interruptions
	Init_Device();
  //SerialIn.Etat_Commande = mogo_1_2;
//	SerialIn.Vitesse_Mot1 = 20;
//	SerialIn.Vitesse_Mot2 = 20;
	
	// Config UARTs
	CFG_Clock_UART ();
	CFG_UART0 ();
	CFG_UART1 ();
	init_Serial_Buffer_0(&SerialIn);  
	init_Serial_Buffer_1();  
  EA = 1;                              /* allow interrupts to happen */
	

	//traitement_Cmd(c);
	while (1)	{
		char c;
		serOutchar_1('g');
		c=serInchar_1();
		if(c != 0)
			serOutchar_1(c);
		
		//Send_Buff_To_Struct_Commande(CentralOut);

		//_nop_ ();
		//deplacement_base(&SerialIn,&CentralOut);

		
		//Putchar("U");
	
}
}
