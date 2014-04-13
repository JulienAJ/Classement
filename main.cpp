#include <iostream>
#include "classement.hpp"
using namespace std;

int main(){

    int choix = 0;
    cout << "Entrez 1 pour creer un nouveau classement" << endl;
    cout << "Entrez 2 pour charger un classement existant" << endl;
    cout << "Entrez autre chose pour quitter" << endl;
    cin >> choix;

    if(choix == 1){

        int temp;
        cout << "Entrez le nombre d'equipes :" << endl;
        cin >> temp;
        while(temp%2 != 0){
            cout << "Veuillez entrer un nombre pair" << endl;
            cout << "Nombre d'equipes :" << endl;
            cin >> temp;
        }
        classement C(temp);
        C.remplir();
        C.afficher_v2();
        C.menu();
    }

    else if(choix == 2){

        string fichier;
        cout << "Entrez le nom du fichier a ouvrir, extension comprise (.txt) :" << endl;
        cin >> fichier;
        classement C(fichier);
        C.afficher_v2();
        C.menu();
    }

    cout << "Session terminee" << endl;
    return 0;
}

/*
actualisation par journee
export match
securité
*/
