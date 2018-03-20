#ifndef SRUCTURE_PC_COMMANDE_H
#define STRUCTURE_PC_COMMANDE_H


typedef unsigned char BYTE;
typedef char SIGNED_BYTE;

///*****************************************************************************************************************************************
// Structure de données pour les commandes transmises par la centrale ce commande
// Les commandes décodées par FO-M1 seront stockées dans une structure de ce type pour être utilisées par FO-M5 
//*****************************************************************************************************************************************

enum Epreuve {Epreuve_non, epreuve1, epreuve2, epreuve3, epreuve4, epreuve5, epreuve6, epreuve7, epreuve8, Fin_Epreuve, Stop_Urgence};
enum Mouvement {Mouvement_non, Avancer, Reculer, Stopper, Rot_90D, Rot_90G, Rot_180D, Rot_180G, Rot_AngD, RotAngG, Depl_Coord}; 
enum ACQ_Son {ACQ_non, ACQ_oui};
enum DCT_Obst {DCT_non, oui_180, oui_360};
enum Lumiere {Lumiere_non, Allumer, Eteindre};
enum Servo {Servo_non, Servo_H, Servo_V};
enum Energie{Energie_non,Mesure_I,Mesure_E};
enum Position{Position_non, Init_Position, Demande_Position};
enum Photo{Photo_non,Photo_1,Photo_Multiple,Photo_continue,Photo_stop}; 

typedef struct COMMANDES       // Cette structure contient toutes les commandes envoyées par la centrale de commande
                               // Les variables de type enum correspondent aux commandes
                               // Les variables de type BYTE, UNSIGNED_BYTE ou int correspondent aux paramètres
                
{           
   enum  Epreuve Etat_Epreuve;     //Contient le numéro d'épreuve en cours - Commandes "D" "E" "Q"	//
   
   enum  Mouvement Etat_Mouvement; //Contient le type de mouvement demandé - Commandes "A"(Avancer) "B"(Reculer) "S"(stop) "RD"(Droite 90) "RG"(Gauche 90) "RC"(dflt Droite 180) "RA"(Rot. Angle) "G"(Déplacement coords.)
                                   // Paramètres des commandes précédentes:     
   BYTE  Vitesse;                  // Paramètre vitesse - Peut aussi être modifié par la commande "TV"
   BYTE  Coord_X;	                 // Paramètre coordonnée X
   BYTE  Coord_Y;                  // Paramètre coordonnée Y
   int   Angle;                    // Paramètre angle
   
   enum  ACQ_Son Etat_ACQ_Son;     // Contient la commande d'acquisition de signaux sonores "ASS"
                                   // Paramètre de la commande précédente:     
   BYTE  ACQ_Duree;                // Paramètre durée de la séquence d'acquisition
   
   enum  DCT_Obst Etat_DCT_Obst;   // Contient la commande de détection d'obstacle "MOB D" "MOB"
                                   // Paramètre de la commandes précédente:     
   BYTE  DCT_Obst_Resolution;      // Paramètre résolution angulaire de la détection d'obstacle
   
   enum  Lumiere Etat_Lumiere;     // Contient la commande d'allumage du pointeur lumineux "L" "LS"
                                   // Paramètres de la commande précédente:     
   BYTE  Lumiere_Intensite;        // Paramètre intensité lumineuse 							  
   BYTE  Lumiere_Duree;            // Paramètre durée d'allumage
   BYTE  Lumire_Extinction;        // Paramètre durée d'extinction
   BYTE  Lumiere_Nbre;             // Paramètre nombre de cycles d'allumage/extinction
   
   enum  Servo Etat_Servo;        // Contient la commande de positionnement d'un servo "CS C" "CS H" "CS V" 
                                  // Paramètre de la commande précédente:     
   SIGNED_BYTE  Servo_Angle;      // Paramètre angle de rotation
   enum  Energie Etat_Energie;    // Contient la commande d'envoi du courant instantané ou de l'energie consommée - Commandes "MI" "ME"
   enum  Position Etat_Position;  // Contient les commandes de gestion de la position, initialisation ou demande d'envoi
		                              // de la position - Commandes: "IPO" "POS"		
   BYTE  Pos_Coord_X;	            // Paramètre coordonnée X pour initialisation de la position
   BYTE  Pos_Coord_Y;             // Paramètre coordonnée Y pour initialisation de la position
   int   Pos_Angle;               // Paramètre angle pour initialisation de la position	 
	 enum  Photo Etat_Photo;        // Contient les commandes de la gestion de la prise de photo - Commandes "PPH" "SPH"
	 BYTE  Photo_Duree;	            // Paramètre durée entre 2 photos
   BYTE  Photo_Nbre;              // Paramètre nombre de photos	 
		 
} OUT_M1;



//*****************************************************************************************************************************************
// Structure de données pour les informations à emettre vers la centrale ce commande
// Les données "Informations" produites par FO-M5  seront stockées dans une structure de ce type pour être utilisées par FO-M1 qui devra
// les encoder en messages ASCII 
//*****************************************************************************************************************************************

enum Invite {Invite_non, Invite_oui};
enum BUT_Mouvement {BUT_Atteint_non, BUT_Atteint_oui};
enum BUT_Servo {BUT_Servo_non, BUT_Servo_H, BUT_Servo_V, BUT_Servo_C};
enum RESULT_Courant{RESULT_Courant_non,RESULT_Courant_oui};
enum RESULT_Energie{RESULT_Energie_non,RESULT_Energie_oui};
enum RESULT_Position{RESULT_Position_non,RESULT_Position_oui};
enum RESULT_DCT_Obst {DCT_Obst_non, DCT_Obst_180_oui, DCT_Obst_360_oui};
enum Aux {Aux_non, Aux_oui};

typedef struct INFORMATIONS       // Cette structure contient toutes les informations susceptibles d'être transmises à la centrale de commande
	                                // Les variables de type enum correspondent aux types des informations
                                  // Les variables de type BYTE, UNSIGNED_BYTE ou int correspondent aux paramètres
                
{           
   enum  Invite Etat_Invite;      // Contient l'identificateur information d'invite "I"
                                  // Paramètre de l'information précédente:     
   char  *MSG_Invit;	            //Pointeur sur une chaine de caractère d'invite     
   
   enum  BUT_Mouvement Etat_BUT_Mouvement; // Contient l'identificateur information Arrivée au point spécifié "B"
	                                         // Pas de paramètre associé pour l'information précédente:     
   enum  BUT_Servo Etat_BUT_Servo;         // Contient l'identificateur information Servomoteur positionné "AS C" "AS H" "AS H"
	                                         // Pas de paramètre associé pour l'information précédente:     
	 
   enum  RESULT_DCT_Obst Etat_DCT_Obst;    // Contient l'identificateur information Détection des obstacles "KOB"
                                           // Paramètre de l'information précédente:    
	 int   *Tab_Val_Obst;                    //Pointeur sur un tableau de valeurs de distance
	 BYTE	 Nbre_Val_obst;                    //Nombre de points dans le tableau
	 
	 enum RESULT_Courant Etat_RESULT_Courant; // Contient un idendicateur d'information "courant mesuré"
	 unsigned int Mesure_Courant;            // Valeur du courant mesuré en mA   
	 
	 enum RESULT_Energie Etat_RESULT_Energie; // Contient un idendicateur d'information "Energie Consommée"
	 unsigned int Mesure_Energie;            // Valeur de l'énergie consommée depuis le début de l'épreuve
	 
	 enum RESULT_Position Etat_RESULT_Position; // Contient un idendicateur d'information "Position"
   BYTE  Pos_Coord_X;	                     // Information Paramètre coordonnée X
   BYTE  Pos_Coord_Y;                      // Information Paramètre coordonnée Y
   int   Pos_Angle;                        // Information Paramètre angle
	 
   enum   Aux Etat_Aux;                    // Contient l'identificateur information auxiliaires "IA"
                                           // Paramètre de l'information précédente:     
   char  *MSG_Aux;	                       //Pointeur sur une chaine de caractère d'informations auxiliaires  
} IN_M1;
// *******************************************************************************************
#endif