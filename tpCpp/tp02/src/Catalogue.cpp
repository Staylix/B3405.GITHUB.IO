/*************************************************************************
                            Catalogue.cpp
                             -------------------
    début                : 15/11/2017
    auteurs              : B3405 - Etienne et Grégoir
*************************************************************************/

//----------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp)

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
void Catalogue::Afficher() const
{
    unsigned int size = catalog->GetUtilise();
    if (size > 0 )
    {
        cout << endl << "Le catalogue contient " << size << " trajets :" << endl;
        for (unsigned int i = 0; i < size; i++)
        {
            cout << i+1 << " - ";
            if (catalog->Get(i) != nullptr)
            {
                catalog->Get(i)->Afficher();
            }
            else
            {
                cout << "null pointer..." << endl;
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Le catalogue est vide..." << endl;
    }
}

void Catalogue::AjouterTrajet(const Trajet * T)
{
  catalog->Add(T);
}

void Catalogue::RechercherSimple(const char * depart, const char * arrivee) const
{
    cout << endl << "******************************************" << endl;
    cout << "Parcours directs disponibles pour faire " << depart << " --> " << arrivee << " :" << endl;
    for (unsigned int i = 0; i < catalog->GetUtilise(); i++)
    {
        if ( !strcmp(depart, catalog->Get(i)->getDepart()) && !strcmp(arrivee, catalog->Get(i)->getArrivee()))
        {
            catalog->Get(i)->Afficher();
        }
    }
    cout << "******************************************" << endl << endl;
}

void Catalogue::RechercherAvancee(const char * depart, const char * arrivee) const
{
    cout << endl << "******************************************" << endl;
    cout << "Parcours disponibles pour faire " << depart << " --> " << arrivee << " :" << endl << endl;
    int * utilise = new int[catalog->GetUtilise()];
    for (unsigned int i = 0; i < catalog->GetUtilise(); i++)
    {
        for (unsigned int j = 0; j < catalog->GetUtilise(); j++)
            {
                utilise[j] = 0;
            }
        if ( !strcmp(depart, catalog->Get(i)->getDepart()) )
        {
            utilise[i] = 1;
            this->recure(utilise, 2, i, arrivee);
        }
    }
    cout << "******************************************" << endl << endl;
    delete [] utilise;
}


//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
    catalog = new TabTrajet();
} //----- Fin de Catalogue

Catalogue::~Catalogue ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    delete catalog;
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées

void Catalogue::recure(int utilise[], int numeroTrajet, int trajetPrecedent , const char * arriveeFinale) const
{
    if (!strcmp(catalog->Get(trajetPrecedent)->getArrivee(), arriveeFinale))
    {
        this->AfficherParcours(utilise);
        return;
    }
    for (unsigned int i = 0; i < catalog->GetUtilise(); i++)
    {
        if ( !strcmp(catalog->Get(i)->getDepart(), catalog->Get(trajetPrecedent)->getArrivee()) && utilise[i] == 0)
        {
            utilise[i] = numeroTrajet;
            this->recure(utilise, numeroTrajet + 1, i, arriveeFinale);
            utilise[i] = 0;
        }
    }
}

void Catalogue::AfficherParcours(int utilise[]) const
{
    int indiceMax = this->max(utilise);
    cout << "--------------------------" << endl;
    for (int j = 1; j <= indiceMax; j++)
    {
        for (unsigned int i = 0; i < catalog->GetUtilise(); i++)
        {
            if (j == utilise[i])
            {
                catalog->Get(i)->Afficher();
            }
        }
    }
}

int Catalogue::max(int utilise[]) const // On sait que utilise est de la taille de catalog
{
    int maxi = 0;
    for (unsigned int i = 0; i < catalog->GetUtilise(); i++)
    {
        if (utilise[i] > maxi) maxi = utilise[i];
    }
    return maxi;
}
