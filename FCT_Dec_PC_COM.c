#include <c8051f020.h>                    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include <CFG_Globale.h>
#include <UART1_RingBuffer_lib.h>
#include <Structure_PC_COmmande.h>
#ifndef CFG_Globale
   #define CFG_Globale
   #include <CFG_Globale.h>
#endif
//*********************************************
//Initialisation du buffer etde l'UART
//*********************************************
void Init_UART_Buffer(void){
	cfg_Clock_UART1();
	cfg_UART1_mode1();
	init_Serial_Buffer1();
}

//********************************************
//Envoie des commandes venues du PC vers la structure
//********************************************
void  Send_Buff_To_Struct_Commandes (struct STRCUTURE_PC_COMMANDE* commande){
	
	unsigned int commande_recu;
	unsigned int type_commande;
	
	
	commande_recu = serInchar1();
	
	switch (commande_recu){
		
		case 'D':
			type_commande = serInchar1();
			if (type_commande == ' '){
				type_commande = serInchar1();
			}
			switch (type_commande){
				commande Etat_
				case '1': com.Etat_Epreuve = 'epreuve1';
				break;
				
				case '2': commande.Etat_Epreuve = 'epreuve2';
				break;
				
				case '3': commande.epreuve = 'epreuve3';
				break;

				case '4': commande.epreuve = 'epreuve4';
				break;
				
				case '5': commande.epreuve = 'epreuve5';
				break;
				
				case '6': commande.epreuve = 'epreuve6';
				break;
				
				case '7': commande.epreuve = 'epreuve7';
				break;
				
				case '8': commande.epreuve = 'epreuve8';
				break;
			}
				
				
	}
	
}
