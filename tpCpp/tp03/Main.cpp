/*************************************************************************
                    Main.cpp  -  Implémente le menu et appelle les tests
                             -------------------
    début                : 15/11/2017
    auteurs              : B3405 - Etienne et Grégoir
*************************************************************************/

#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Trajet.h"
#include "TabTrajet.h"
#include "Catalogue.h"

//----------TESTS
#include "TestUnit.h"


static void print_option()
{
  cout << "\t1 - Ajouter un trajet simple au catalogue" << endl;
  cout << "\t2 - Ajouter un trajet composé au catalogue" << endl;
  cout << "\t3 - Afficher le catalogue" << endl;
  cout << "\t4 - Chercher un voyage direct" << endl;
  cout << "\t5 - Chercher un voyage avec correspondance éventuelle" << endl;
  cout << "\t6 - Sauvegarder le catalogue dans un fichier" << endl;
  cout << "\t7 - Charger le catalogue depuis un fichier" << endl;
  cout << "\t8 - Choisir le fichier de sauvegarde" << endl;
  cout << "\t0 - Quitter" << endl << endl;
}

static void print_option_svg()
{
  cout << "\t\t1 - Tout le catalogue" << endl;
  cout << "\t\t2 - Seulement les trajets simples" << endl;
  cout << "\t\t3 - Seulement les trajets composés" << endl;
  cout << "\t\t4 - Selon la ville de départ" << endl;
  cout << "\t\t5 - Selon la ville d'arrivée" << endl;
  cout << "\t\t6 - Selon les villes de départ et d'arrivée" << endl;
  cout << "\t\t7 - Une selection de trajets" << endl;
}

unsigned int readChoice( int min, int max )     // Lit un chiffre uniquement, compris entre min et max
{
    string choiceS;
    unsigned int choice;
    bool ok = false;
    while (!ok)
    {
        getline(cin, choiceS);
        if ( choiceS.size() == 1 && int(choiceS[0]) >= 48 + min && int(choiceS[0]) <= 48 + max )
        {
            ok = true;
        }
        else
        {
            cout << "Saisie incorrecte, réessayez :" << endl;
        }
    }
    choice = stoi(choiceS);
    return choice;
}
unsigned int readChoice()       // Lit un nombre uniquement
{
    string choiceS;
    unsigned int choice;
    bool ok = false;
    while (!ok)
    {
        ok = true;
        getline(cin, choiceS);
        for ( unsigned int i = 0; i < choiceS.size(); i ++ )
        {
            if ( !(int(choiceS[i]) >= 48 && int(choiceS[i]) <= 57) )
            {
                ok = false;
            }
        }
        if (!ok)
        {
            cout << "Saisie incorrecte, réessayez :" << endl;
        }
    }
    choice = stoi(choiceS);
    return choice;
}


int main()
{
  test();

  Catalogue *MonCatalogue = new Catalogue();

  string fichier = "demo.txt";      // Fichier de sauvegarde courant

  unsigned int choix;
  unsigned int nbTrajets;
  string depart;
  string arrivee;
  string moyen;

  cout << "*******************************************" << endl;
  cout << "* Bienvenue dans votre agence de voyage ! *" << endl;
  cout << "*******************************************" << endl;
  cout << "Que voulez vous faire ?" << endl << endl;
  print_option();


  choix = readChoice(0, 8);
  while (choix != 0)
  {
    if (choix == 1)     // Ajout de trajet simple
    {
      cout << "Veulliez saisir votre trajet :" << endl;
      cout << "Départ : ";
      getline(cin, depart);
      cout << "Arrivée : ";
      getline(cin, arrivee);
      cout << "Moyen de transport : ";
      getline(cin, moyen);
      const Trajet * trajet = new const TrajetSimple(depart, arrivee, moyen);
      MonCatalogue->AjouterTrajet(trajet);
      cout << "Trajet ajouté !" << endl;
    }

    else if (choix == 2)     // Ajout de trajet composé
    {
      cout << "Combien de trajets simples composent votre trajet ?" << endl;
      nbTrajets = readChoice();
      if (nbTrajets > 1)
      {
        TabTrajet * tab = new TabTrajet();
        cout << "Veulliez saisir vos trajets :" << endl;
        bool valide = true;
        for (unsigned int i = 0; i < nbTrajets; i++)
        {
            cout << "Trajet n°" << i+1 << " :" << endl;
            cout << "\tDépart : ";
            getline(cin, depart);
            if (i > 0 && depart != arrivee)
            {
                cout << "Votre trajet n'est pas valide..." << endl;
                valide = false;
                i = nbTrajets;      // On arrête de lire cin
            }
            else
            {
                cout << "\tArrivée : ";
                getline(cin, arrivee);
                cout << "\tMoyen de transport : ";
                getline(cin, moyen);
                const Trajet * sousTrajet = new const TrajetSimple(depart, arrivee, moyen);
                tab->Add(sousTrajet);
            }
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

    else if (choix == 3)     // Affichage du catalogue
    {
      MonCatalogue->Afficher();
    }

    else if (choix == 4)     // Recherche simple
    {
      cout << "Veulliez indiquer le départ et l'arrivée de votre voyage :" << endl;
      getline(cin, depart);
      getline(cin, arrivee);
      MonCatalogue->RechercherSimple(depart, arrivee);
    }

    else if (choix == 5)     // Recherche avancée
    {
        cout << "Veulliez indiquer le départ et l'arrivée de votre voyage :" << endl;
        getline(cin, depart);
        getline(cin, arrivee);
        MonCatalogue->RechercherAvancee(depart, arrivee);
    }

    else if (choix == 6)    // Sauvegarde
    {
        cout << "\tVoulez vous sauvegarder :" << endl << endl;
        print_option_svg();
        choix = readChoice(1, 7);
        if (choix == 1)
        {
            MonCatalogue->Save(fichier);
        }
        else if (choix == 2)
        {
            MonCatalogue->Save(fichier, "TS");
        }
        else if (choix == 3)
        {
            MonCatalogue->Save(fichier, "TC");
        }
        else if (choix == 4)
        {
            cout << "Quelle ville de départ ?" << endl;
            getline(cin, moyen);
            MonCatalogue->Save(fichier, moyen, 0);
        }
        else if (choix == 5)
        {
            cout << "Quelle ville d'arrivée ?" << endl;
            getline(cin, moyen);
            MonCatalogue->Save(fichier, moyen, 1);
        }
        else if (choix == 6)
        {
            cout << "Quelle ville de départ ?" << endl;
            getline(cin, depart);
            cout << "Quelle ville d'arrivée ?" << endl;
            getline(cin, arrivee);
            MonCatalogue->Save(fichier, depart, arrivee);
        }
        else if (choix == 7)
        {
            cout << "Voici les trajets contenus dans le catalogue :" << endl;
            MonCatalogue->Afficher();
            cout << "Lesquels voulez-vous sauvegarder ?" << endl;
            cout << "Du" << endl;
            nbTrajets = readChoice();
            unsigned int tmp = nbTrajets;
            cout << "Au" << endl;
            nbTrajets = readChoice();
            MonCatalogue->Save(fichier, tmp, nbTrajets);
        }
    }

    else if (choix == 7)    // Chargement
    {
        cout << "\tVoulez vous charger :" << endl << endl;
        print_option_svg();
        choix = readChoice(1, 7);
        if (choix == 1)
        {
            MonCatalogue->Lire(fichier);
        }
        else if (choix == 2)
        {
            MonCatalogue->Lire(fichier, "TS");
        }
        else if (choix == 3)
        {
            MonCatalogue->Lire(fichier, "TC");
        }
        else if (choix == 4)
        {
            cout << "Quelle ville de départ ?" << endl;
            getline(cin, moyen);
            MonCatalogue->Lire(fichier, moyen, 0);
        }
        else if (choix == 5)
        {
            cout << "Quelle ville d'arrivee ?" << endl;
            getline(cin, moyen);
            MonCatalogue->Lire(fichier, moyen, 1);
        }
        else if (choix == 6)
        {
            cout << "Quelle ville de départ ?" << endl;
            getline(cin, depart);
            cout << "Quelle ville d'arrivée ?" << endl;
            getline(cin, arrivee);
            MonCatalogue->Lire(fichier, depart, arrivee);
        }
        else if (choix == 7)
        {
            cout << "Voici les trajets contenus dans le fichier " << fichier << " :" << endl;
            Catalogue * tmpCatalogue = new Catalogue();
            tmpCatalogue->Lire(fichier);
            tmpCatalogue->Afficher();
            delete tmpCatalogue;
            cout << "Lesquels voulez-vous charger ?" << endl;
            cout << "Du" << endl;
            nbTrajets = readChoice();
            unsigned int tmp = nbTrajets;
            cout << "Au" << endl;
            nbTrajets = readChoice();
            MonCatalogue->Lire(fichier, tmp, nbTrajets);
        }
    }

    else if (choix == 8)    // Choix du fichier
    //  Si le fichier choisi n'existe pas, le chargement est impossible
    //  et le fichier est créé lors d'une sauvegarde
    {
        cout << "Le fichier actuel est : " << fichier << endl;  // Fichier par défaut : demo.txt
        cout << "Entrez le nom complet du fichier :" << endl;
        getline(cin, fichier);
    }

    cout << endl << "Maintenant, que voulez vous faire ?" << endl << endl;
    print_option();
    choix = readChoice(0, 8);
  }   // Fin du while

  cout << "Good bye and have a nice trip ! ;)" << endl;
  delete MonCatalogue;
  return 0;
}
