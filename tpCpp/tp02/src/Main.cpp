/*************************************************************************
                    Main.cpp  -  Implémente le menu et appelle les tests
                             -------------------
    début                : 15/11/2017
    auteurs              : B3405 - Etienne et Grégoir
*************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Trajet.h"
#include "TabTrajet.h"
#include "Catalogue.h"

//----------TESTS
#include "TestUnit.h"

//----------Constante
#define MAX 100

static void print_option() {
  cout << "\t1 - Ajouter un trajet simple au catalogue" << endl;
  cout << "\t2 - Ajouter un trajet composé au catalogue" << endl;
  cout << "\t3 - Afficher le catalogue" << endl;
  cout << "\t4 - Chercher un voyage direct" << endl;
  cout << "\t5 - Chercher un voyage avec correspondance éventuelle" << endl;
  cout << "\t0 - Quitter" << endl << endl;
}

int main()
{
  test();

  Catalogue *MonCatalogue = new Catalogue();
  unsigned int choix = 50;
  int nbTrajets;
  char * depart = new char[MAX];
  char * arrivee = new char[MAX];
  char * moyen = new char[MAX];

  cout << "Bonjour et bienvenu dans votre agence de voyage !" << endl;
  cout << "Que voulez vous faire ?" << endl << endl;
  print_option();

  cin >> choix;
  while (choix != 0)
  {
    if (choix == 1)     // Ajout de trajet simple
    {
      cout << "Veulliez indiquer le départ, l'arrivée et le moyen de transport de votre trajet :" << endl;
      cin >> depart;
      cin >> arrivee;
      cin >> moyen;
      const Trajet * trajet = new const TrajetSimple(depart, arrivee, moyen);
      MonCatalogue->AjouterTrajet(trajet);
      cout << "Trajet ajouté !" << endl;
    }

    if (choix == 2)     // Ajout de trajet composé
    {
      cout << "Combien de trajets simples composent votre trajet ?" << endl;
      cin >> nbTrajets;
      if (nbTrajets > 1)
      {
        TabTrajet * tab = new TabTrajet();
        cout << "Veulliez indiquer le départ, l'arrivée et le moyen de transport de chaque étape :" << endl;
        bool valide = true;
        for (int i = 0; i < nbTrajets; i++)
        {
            cin >> depart;
            if (i > 0 && strcmp(depart, arrivee))
            {
                cout << "Votre trajet n'est pas valide..." << endl;
                valide = false;
                i = nbTrajets; // On arrête de lire cin
            }
            cin >> arrivee;
            cin >> moyen;
            const Trajet * sousTrajet = new const TrajetSimple(depart, arrivee, moyen);
            tab->Add(sousTrajet);
        }
        const Trajet * trajet = new const TrajetCompose(tab);
        if (valide)
        {
            MonCatalogue->AjouterTrajet(trajet);
            cout << "Trajet ajouté !" << endl;
        }
        else
        {
            delete trajet;
        }
      }
      else
      {
        cout << "Ce n'est pas très utile..." << endl;
      }
    }

    if (choix == 3)     // Affichage du catalogue
    {
      MonCatalogue->Afficher();
    }

    if (choix == 4)     // Recherche simple
    {
      cout << "Veulliez indiquer le départ et l'arrivée de votre voyage :" << endl;
      cin >> depart;
      cin >> arrivee;
      MonCatalogue->RechercherSimple(depart, arrivee);
    }

    if (choix == 5)     // Recherche avancée
    {
        cout << "Veulliez indiquer le départ et l'arrivée de votre voyage :" << endl;
        cin >> depart;
        cin >> arrivee;
        MonCatalogue->RechercherAvancee(depart, arrivee);
    }

    cout << endl << "Maintenant, que voulez vous faire ?" << endl << endl;
    print_option();
    cin >> choix;
  }   // Fin du while

  cout << "Good bye and have a nice trip ! ;)" << endl;
  delete [] depart;
  delete [] arrivee;
  delete [] moyen;
  delete MonCatalogue;
  return 0;
}
