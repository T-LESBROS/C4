/*
typedef unsigned char BYTE;
typedef char SIGNED_BYTE;
*/

#include "FO_M1_Structures_COMMANDES_INFORMATIONS_CentraleDeCommande.c"

//*****************************************************************************************************************************************
// Structure de données pour les commandes à envoyer à la carte Serializer
// Les commandes produites par FO-M5 (à priori) seront stockées dans une structure de ce type pour être utilisées par FO-M2
// Cette structure ne couvre pas toutes les commandes compréhensibles par la carte Serializer. 
// Seules les commande potentiellement utiles au projet SEM818 sont traitées 
// Commandes Traitées:  Reset - getenc - clrenc - mogo - vpid - digo - dpid - rpid - pids - stop - vel - restore
//*****************************************************************************************************************************************

enum Commande {Commande_non, Reset, Getenc_1, Getenc_2, Getenc_1_2, Clrenc_1, Clrenc_2, Clrenc_1_2, mogo_1, mogo_2, mogo_1_2, Vpid_set, Vpid_read,
               digo_1, digo_2, digo_1_2, Dpid_set, Dpid_read, Rpid_Stinger, Pids, Stop, Vel, Restore };


typedef struct COMMANDES_SERIALIZER  // Cette structure contient toutes les commandes à envoyer au serializer
	                                   // Les variables de type enum correspondent aux commandes
                                     // Les variables de type BYTE, UNSIGNED_BYTE ou int correspondent aux paramètres
                
{           
   enum  Commande Etat_Commande;   // Contient la commande à transmettre "Reset" "getenc 1" "getenc 2" "getenc 1 2" "clrenc 1" "clrenc 2"
                                   // "clrenc 1 2" "mogo 1" "mogo 1" "mogo 2" "mogo 1 2" "vpid" "digo 1" "digo 2" "digo 1 2" "dpid"
									                 // "rpid s"  "pids" "stop" "vel" "restore"
               
   int   Set_P;                    // paramètre commande vpid dpid
   int   Set_I;                    // paramètre commande vpid dpid
   int   Set_D;                    // paramètre commande vpid dpid
   int   Set_L_A;                  // paramètre commande vpid (L)  dpid (A)
   int   Ticks_mot1;               // paramètre Distance - Encoder Ticks moteur 1 (digo)
   SIGNED_BYTE  Vitesse_Mot1;      // paramètre de vitesse de rotation du moteur 1  (mogo digo)
   int   Ticks_mot2;               // paramètre Distance - Encoder Ticks moteur 2 (digo)
   SIGNED_BYTE  Vitesse_Mot2;      // paramètre de vitesse de rotation du moteur 2 (mogo digo)
} IN_M2;


//*****************************************************************************************************************************************
// Structure de données pour les informations transmises par la carte Serializer
// Les informations Serializer décodées par FO-M2 seront stockées dans une structure de ce type pour être utilisées par FO-M5
// Cette structure ne couvre pas toutes les informations transmissibles par la carte Serializer. 
// Seules les informations potentiellement utiles au projet SEM818 sont traitées 
//*****************************************************************************************************************************************

enum Reponse {Reponse_non, Rep_getenc, Rep_vpid, Rep_dpid, Rep_pids, Rep_vel};


typedef struct INFORMATIONS_SERIALIZER // Cette structure contient toutes les informations envoyées par la carte Serializer
	                                     // Les variables de type enum correspondent aux commandes
                                       // Les variables de type BYTE, UNSIGNED_BYTE ou int corrspondent aux paramètres
                
{  
   enum  Reponse Etat_Response;   	   // Contient le type de réponse reçue à une des commandes suivantes:  "vpid" "dpid" "pids" "vel" 
   int   Read_Val_enc_1;               // information commande getenc1
   int   Read_Val_enc_2;               // information commande getenc2
   
   int   Read_P;                       //   information commande vpid dpid
   int   Read_I;                       //   information commande vpid dpid
   int   Read_D;                       //   information commande vpid dpid
   int   Read_L_A;                     //   information commande vpid (L)  dpid (A)
   BYTE  Read_Pids;                    //   information commande pids
   int   Read_Vitesse_mot1;            //   information commande "velocity" moteur 1
   int   Read_Vitesse_mot2;            //   information commande "velocity" moteur 2
   
} OUT_M2;