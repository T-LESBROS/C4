#include <c8051f020.h>                    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include <CFG_Globale.h>
#include <UART1_RingBuffer_lib.h>
#include <Structure_PC_COmmande.h>
#include <LIB_BSE_Config-Globale.h>
#include <Declarations_GPIO_BSE.h>
#include <FCT_Dec_PC_COM.h>
#include <string.h>
#ifndef CFG_Globale
   #define CFG_Globale
   #include <CFG_Globale.h>
#endif
//*********************************************
//Initialisation du buffer et de l'UART
//*********************************************
void Init_UART_Buffer(void){
	cfg_Clock_UART1();
	cfg_UART1_mode1();
	init_Serial_Buffer1();
	
	//Watch dogs
		WDTCN = 0xde;
		WDTCN = 0xad;
	
	//

}

//********************************************
//Envoie des commandes venues du PC vers la structure
//********************************************

void  Send_Buff_To_Struct_Commandes (struct COMMANDES* commande){

	
	//récupération et concaténation de la commande
	
	char caract_buff_lu;
	char commande_entiere[10];
	//char* case_commande= &commande_entiere[0];
	int i=0;
	//unsigned int test;
	char caract_actuel;
	//test = 0x20;
	
	while (caract_buff_lu != 0x0D)
	{
		caract_buff_lu = serInchar1();
	 //while (test != 0x0D){
		if (caract_buff_lu = 0x20){
		//if (test == 0x20){
			continue;
			//test = 'A';
		}
		else 
		{
			commande_entiere[i] = caract_buff_lu;
			//commande_entiere[i]=test;
			i+=1;
			//test = 0x0D;
		}
	}
	
		if (commande_entiere[0]=='B'){
			commande->Etat_Epreuve = epreuve1;
		}
		
		else
		{
			commande->Etat_Epreuve = epreuve2;
		}
	/*	
		//if (commande_recu = 'D')

		for( i=0, i<=10, i++){
		
			caract_actuel=commande_entiere[i];
			
		switch (caractère_actuel){
		
			case 'D':
			//	type_commande = serInchar1();
			//	if (type_commande == 0x20){
			//		type_commande = serInchar1();
		  
				}
				switch (type_commande){

					case '1': commande->Etat_Epreuve = epreuve1;
					break;
					
					case '2': commande->Etat_Epreuve = epreuve2;
					break;
					
					case '3': commande->Etat_Epreuve = epreuve3;
					break;

					case '4': commande->Etat_Epreuve = epreuve4;
					break;
					
					case '5': commande->Etat_Epreuve = epreuve5;
					break;
					
					case '6': commande->Etat_Epreuve = epreuve6;
					break;
					
					case '7': commande->Etat_Epreuve = epreuve7;
					break;
					
					case '8': commande->Etat_Epreuve = epreuve8;
					break;
				}
				
		}
				
					
		}
		*/
	}	
	
	//**********************************************************
//void main test
void main (void){
	struct COMMANDES* commande;
	
	Init_UART_Buffer();
	Init_Device();
	
	
	
	
	
	while(1){
		Send_Buff_To_Struct_Commandes(commande);
	}
	

	
	
}
