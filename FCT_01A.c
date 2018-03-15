#include <C8051F020.h>
#include <stdio.h>


//#include "FO_M1_Structures_COMMANDES_INFORMATIONS_CentraleDeCommande.c"
#include "FO_M2_Structures_COMMANDES_INFORMATIONS_Serializer.c"
#include "FCT_01A.h"
	
IN_M2 Serial;				//Pointeurs des structures
OUT_M1 Central;
//OUT_M1 *comCent = &Central;

// Switch bas� sur la structure OUT_M1, permettant d'�crire dans IN_M2

void deplacement_base(void)
{
	/*
	Pour tester :
	Central.Etat_Mouvement = Avancer;
	comCent->Etat_Mouvement = Reculer;
	Central.Vitesse = 2;*/
	Central.Etat_Mouvement = Avancer;
	

	switch (Central.Etat_Mouvement)
	{
		case 0x01 : deplacer(0);														// Si Etat_Mouvement = Avancer
								break;

		case 0x02 : deplacer(1);														// Si Etat_Mouvement = Reculer
								break;

		case 0x03 : arret();																// Si Etat_Mouvement = Stopper	
								break;

		case 0x04 : tourner(1);												  	// Si Etat_Mouvement = Rot_90D
								break;

		case 0x05 : tourner(0);												  	// Si Etat_Mouvement = Rot_90G
								break;

		default : arret();															//Comportement par d�faut : On est � l'arr�t; Etat_Mouvement = Mouvement_non
								break;
	}
}

// Fonctions donnant le d�tail de ce qui est �cris dans IN_M2

void deplacer(int reculer)
{
	int vitesse = Central.Vitesse;
	if (reculer)
	{
		vitesse = - vitesse;
	};

	Serial.Etat_Commande = mogo_1_2;
	Serial.Vitesse_Mot1 = vitesse;
	Serial.Vitesse_Mot2 = vitesse;

}

void tourner(int tourne_droite)
{
	if (tourne_droite)								//simule le bool�en tourne � droite
		{
		Serial.Etat_Commande = mogo_1;
		Serial.Vitesse_Mot1 = 20;			//pas s�r de quelle roue correspond � quel moteur, � v�rifier
			
		}
		
	else
	{
	  Serial.Etat_Commande = mogo_2;
		Serial.Vitesse_Mot2 = 20;
	}
		
}

void arret(void)
{
	Serial.Etat_Commande = Stop;
}