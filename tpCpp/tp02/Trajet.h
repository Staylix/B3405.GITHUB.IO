/*************************************************************************
                           Trajet.h  -  Interface de TrajetSimple et TrajetCompose
                                        Classe purement abstraite
                           -------------------
    début                : 15/11/2017
    copyright            : (C) $YEAR$ par Greg & Etienne
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Trajet> (fichier Trajet.h) -------------------
#if ! defined ( Trajet_H )
#define Trajet_H

//------------------------------------------------------------------------
// Rôle du module <Trajet>
// Déclare les méthodes implémentées dans les classes enfants
// 
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types


class Trajet {
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

public:
    
    virtual ~Trajet() {};

    virtual char * getDepart() const = 0;
    virtual char * getArrivee() const = 0;
    // Mode d'emploi :
    //      Renvoie le départ ou l'arrivée

    virtual void Afficher() const = 0;
    // Mode d'emploi :
    //      Affiche le Trajet
};
#endif // Trajet_H
