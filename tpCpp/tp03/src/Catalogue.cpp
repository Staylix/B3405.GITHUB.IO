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
#include "TrajetSimple.h"
#include "TrajetCompose.h"

string fichier = "demo.txt";

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

void Catalogue::RechercherSimple(const string & depart, const string & arrivee) const
{
    cout << endl << "******************************************" << endl;
    cout << "Parcours directs disponibles pour faire " << depart << " --> " << arrivee << " :" << endl;
    for (unsigned int i = 0; i < catalog->GetUtilise(); i++)
    {
        if ( depart == catalog->Get(i)->getDepart() && arrivee == catalog->Get(i)->getArrivee() )
        {
            catalog->Get(i)->Afficher();
        }
    }
    cout << "******************************************" << endl << endl;
}

void Catalogue::RechercherAvancee(const string & depart, const string & arrivee) const
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
        if ( depart == catalog->Get(i)->getDepart() )
        {
            utilise[i] = 1;
            this->recure(utilise, 2, i, arrivee);
        }
    }
    cout << "******************************************" << endl << endl;
    delete [] utilise;
}

void Catalogue::Save() const
{
    ofstream os(fichier, ios::out | ios::app);
    for (unsigned int i = 0; i < this->catalog->GetUtilise(); i++)
    {
        this->catalog->Get(i)->Ecrire(os);
        // Eventuel séparateur : os << "";
    }
    os.close();
}
void Catalogue::Save(string) const
{

}
void Catalogue::Save(string, string) const
{

}
void Catalogue::Save(int, int) const
{

}

void Catalogue::Lire()
{
    string depart;
    string arrivee;
    string moyen;
    ifstream is(fichier, ios::in);
    unsigned int nb;
    string nbS;
    getline(is, moyen);
    while (!is.eof())
    {
        if (moyen == "TC")
        {
            TabTrajet * tab = new TabTrajet();
            getline(is, nbS);
            nb = stoi(nbS);
            getline(is, depart);
            getline(is, arrivee);
            for (unsigned int i = 0; i < nb; i++)
            {
                getline(is, depart);
                getline(is, arrivee);
                getline(is, moyen);
                const Trajet * sousTrajet = new const TrajetSimple(depart, arrivee, moyen);
                tab->Add(sousTrajet);
            }
            const Trajet * trajet = new const TrajetCompose(tab);
            this->AjouterTrajet(trajet);
        }
        else
        {
            getline(is, depart);
            getline(is, arrivee);
            getline(is, moyen);
            const Trajet * trajet = new const TrajetSimple(depart, arrivee, moyen);
            this->AjouterTrajet(trajet);
        }
        getline(is, moyen);
    }
}
void Catalogue::Lire(string)
{

}
void Catalogue::Lire(string, string)
{

}
void Catalogue::Lire(int, int)
{

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

void Catalogue::recure(int utilise[], int numeroTrajet, int trajetPrecedent , const string & arriveeFinale) const
{
    if (catalog->Get(trajetPrecedent)->getArrivee() == arriveeFinale)
    {
        this->AfficherParcours(utilise);
        return;
    }
    for (unsigned int i = 0; i < catalog->GetUtilise(); i++)
    {
        if ( catalog->Get(i)->getDepart() == catalog->Get(trajetPrecedent)->getArrivee() && utilise[i] == 0 )
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
