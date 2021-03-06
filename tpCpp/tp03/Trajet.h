/*************************************************************************
                    Trajet.h  -  Interface de TrajetSimple et TrajetCompose
                                 Classe purement abstraite
                           -------------------
    début                : 15/11/2017
    auteurs              : B3405 - Etienne et Grégoire
*************************************************************************/

//---------- Interface du module <Trajet> (fichier Trajet.h) -------------
#if ! defined ( Trajet_H )
#define Trajet_H

//------------------------------------------------------------------------
// Rôle du module <Trajet>
// Déclare les méthodes implémentées dans les classes enfants :
// TrajetSimple et TrajetCompose
//------------------------------------------------------------------------
#include <fstream>
#include <string>

class Trajet {
public:

//------------------------------------------------------------- Destructor
    virtual ~Trajet() {};

//---------------------------------------------------- Fonctions publiques
    virtual string getDepart() const = 0;
    virtual string getArrivee() const = 0;
    virtual string getMoyen() const = 0;
    // Contrat :
    //      Renvoie le départ ou l'arrivée du trajet appelant la méthode

    virtual void Afficher() const = 0;
    // Contrat :
    //      Affiche le trajet appelant la méthode

    virtual void Ecrire(ofstream & os) const = 0;
    virtual void Ecrire(ofstream & os, string type) const = 0;
    // Contrat :
    //      Ecrit le trajet appelant la méthode dans le fichier manipulé
    //      par le flux en paramètre
    //      La méthode surchargée écrit dans le fichier seulement si
    //      le trajet est du type spécifié par type


};
#endif // Trajet_H
