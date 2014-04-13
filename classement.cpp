#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "classement.hpp"
using namespace std;

classement::classement(){

	taille = 0;
	T = NULL;
}

classement::classement(int t){

	taille = t;
	T = new team[t];
	int matchs = (t/2)*((t-1)*2);
	M = new match[matchs];
}

classement::classement(string nom_fichier){

    charger(nom_fichier);
}

classement::~classement(){

	taille = 0;
	delete [] T;
	delete [] M;
}

int classement::longMax(){

    int max = 0;
    int temp = 0;
    for(int i = 0; i < taille; i++){
        temp = T[i].nom.size();
        if(temp > max)
            max = T[i].nom.size();
    }
    return max;
}

void classement::afficher_team_v2(int indice){

    int tailleMax = longMax();
    cout << (indice+1) << '\t';
    cout << T[indice].nom;
    espacer(tailleMax-T[indice].nom.size()+1);
	cout << T[indice].points << '\t';
	cout << T[indice].joues << '\t';
	cout << T[indice].gagnes << '\t';
	cout << T[indice].nuls << '\t';
	cout << T[indice].perdus << '\t';
    cout << T[indice].bpour << '\t';
	cout << T[indice].bcontre << '\t';
	cout << T[indice].diff << endl;
}

void classement::espacer(int nb){

    for(int i = 0; i < nb; i++)cout << ' ';
}

void classement::afficher_v2(){

    int size = longMax();
    cout << "Pos" << '\t';
    cout << "Nom";
    espacer(size-2);
    cout << "Pts" << '\t' << "J" << '\t';
	cout << "G" << '\t' << "N" << '\t' << "P" << '\t';
	cout << "BP" << '\t' << "BC" << '\t' << "Diff"  << endl;
	for(int i = 0; i < taille; i++){
		afficher_team_v2(i);
	}
	cout << endl;
}

bool classement::superieure(int i, int j){

	if(T[i].points > T[j].points)return true;
	if(T[i].points < T[j].points)return false;
	if(T[i].diff > T[j].diff)return true;
	if(T[i].diff < T[j].diff)return false;
	if(T[i].bpour > T[j].bpour)return true;
	if(T[i].bpour < T[j].bpour)return false;
    if(T[i].bcontre < T[j].bcontre)return true;
    return false;
}

void classement::echanger(int i, int j){

	team temp;
	temp = T[i];
	T[i] = T[j];
	T[j] = temp;
}

void classement::tri(){

   int i;
   int longueur = taille;
   bool permutation;
   do{
      permutation = false;
      for(i=0; i<longueur-1; i++){
         if(superieure(i+1, i)){
            echanger(i, i+1);
            permutation = true;
         }
      }
      longueur--;
   }
   while(permutation);
}

void classement::setTeam(int i, string name){

	T[i].nom = name;
	T[i].points = 0;
	T[i].joues = 0;
	T[i].diff = 0;
	T[i].gagnes = 0;
	T[i].nuls = 0;
	T[i].perdus = 0;
	T[i].bpour = 0;
	T[i].bcontre = 0;
}

void classement::remplir(){

	string temp;
	for(int i = 0; i < taille; i++){
		cout << "Entrez le nom de l'equipe " << i+1 << " :" << endl;
		cin >> temp;
		cout << endl;
		setTeam(i, temp);
	}
	planifier();
}

void classement::planifier(){

    int c = 0;
    for(int i = 0; i < taille; i++){

        for(int y = 0; y < taille; y++){
            if(i != y){
                M[((taille-1)*i)+c].dom = T[i].nom;
                M[((taille-1)*i)+c].ext = T[y].nom;
                M[((taille-1)*i)+c].BD = -1;
                M[((taille-1)*i)+c].BE = -1;
                M[((taille-1)*i)+c].journee = 0;
                c++;
            }
        }
        c = 0;
    }
    dater();
}

void classement::dater(){

        int temp;
        for(int i = 0; i < (taille/2)*((taille-1)*2); i++){
            afficher_match(i);
            cout << "Ce match se jouera lors de quelle journee ?" << endl;
            cin >> temp;
            while(temp < 1 || temp > (taille-1)*2){
                cout << "Veuillez entrer un nombre compris entre 1 et " << (taille-1)*2 << endl;
                cin >> temp;
            }
            M[i].journee = temp;
        }
}

void classement::afficher_match(int i){

    int tailleMax = longMax();
    cout << M[i].dom;
    espacer(tailleMax-M[i].dom.size()+1);
    if(M[i].BD == -1) cout << " ";
    else cout << M[i].BD;
    cout << " " << "-" << " ";
    if(M[i].BE == -1) cout << " ";
    else cout << M[i].BE;
    espacer(tailleMax-M[i].ext.size()+1);
    cout << M[i].ext << endl;
}

void classement::afficher_journee(int jour, int mode){

    cout << "Journee " << jour << " :" << endl;
    int num = 1;
    for(int i = 0; i < (taille/2)*((taille-1)*2); i++){
        if(M[i].journee == jour){
            if(mode == 1) cout << num;
            afficher_match(i);
            num++;
            }
    }
    if(num == 1)cout << "Aucun match trouve pour cette journee" << endl;
}

void classement::planing(int type){

    if(type == 3){
        for(int i = 1; i <= (taille-1)*2; i++)
            afficher_journee(i, 0);

    }

    else{
        int temp = (taille/2)*((taille-1)*2);
        for(int i = 0; i < temp; i++){
            if(type == 1)cout << i+1 << '\t';
            afficher_match(i);
        }
    }
}

void classement::actualiser_team_v2(int ind, int dom_ext, int BM, int BE){

    int j;
    for(int i = 0; i < taille; i++){
        if(dom_ext == 0 && M[ind].dom == T[i].nom)j = i;
        else if(dom_ext == 1 && M[ind].ext == T[i].nom) j = i;
    }

    if(BM - BE == 0){
		T[j].nuls++;
		T[j].points++;
	}
	else if(BM - BE > 0){
		T[j].gagnes++;
		T[j].points += 3;
	}
	else T[j].perdus++;

    T[j].diff += (BM-BE);
    T[j].bpour += BM;
    T[j].bcontre += BE;
	T[j].joues++;
}

void classement::suppr_match(int i){

    int bdom = M[i].BD;
    int bext = M[i].BE;

    int teamd, teame;

    for(int j = 0; j < taille; j++){
        if(T[j].nom == M[i].dom) teamd = j;
        if(T[j].nom == M[i].ext) teame = j;
    }

    T[teamd].bpour -= bdom;
    T[teamd].bcontre -= bext;
    T[teame].bpour -= bext;
    T[teame].bcontre -= bdom;
    T[teamd].joues -= 1;
    T[teame].joues -= 1;
    T[teamd].diff = T[teamd].bpour - T[teamd].bcontre;
    T[teame].diff = T[teame].bpour - T[teame].bcontre;

    if(bdom == bext){
        T[teamd].points -= 1;
        T[teame].points -= 1;
        T[teamd].nuls -= 1;
        T[teame].nuls -= 1;
    }
    else if(bdom > bext){

        T[teamd].points -= 3;
        T[teamd].gagnes -= 1;
        T[teame].perdus -= 1;
    }
    else{
        T[teame].points -= 3;
        T[teame].gagnes -= 1;
        T[teamd].perdus -= 1;
    }
}

void classement::actualiser_match(int i){

    afficher_match(i);
    if(M[i].BD != -1 || M[i].BE != -1)suppr_match(i);
    cout << endl << "Nombre de buts marques par " << M[i].dom << " " << endl;
    cin >> M[i].BD;
    cout << endl << "Nombre de buts marques par " << M[i].ext << " " << endl;
    cin >> M[i].BE;
    actualiser_team_v2(i, 0, M[i].BD, M[i].BE);
    actualiser_team_v2(i, 1, M[i].BE, M[i].BD);
}

void classement::actualiser_v2(){

    planing(1);
    cout << "Entrez le numero correspondant au match a modifier" << endl;
    int ind;
    cin >> ind;
    actualiser_match(ind-1);
    tri();
}

void classement::enregistrer(){

	string nom_fich;
	cout << "Entrez le nom du fichier a creer sans extension :" << endl;
	cin >> nom_fich;
	ofstream sauve((nom_fich+".txt").c_str(), ios::out);
	if(sauve){
		sauve << taille << endl;
		for(int i = 0; i < taille; i++){

            sauve << T[i].nom << '\t';
            sauve << T[i].points << '\t';
            sauve << T[i].joues << '\t';
            sauve << T[i].gagnes << '\t';
            sauve << T[i].nuls << '\t';
            sauve << T[i].perdus << '\t';
            sauve << T[i].bpour << '\t';
            sauve << T[i].bcontre << '\t';
            sauve << T[i].diff << '\t';
            sauve << endl;

		}
		int match = (taille/2)*((taille-1)*2);
		for(int j = 0; j < match; j++){

            sauve << M[j].dom << '\t';
            sauve << M[j].ext << '\t';
            sauve << M[j].BD << '\t';
            sauve << M[j].BE << '\t';
            sauve << M[j].journee << '\t';
            sauve << endl;
		}
	}
	else cerr << "Erreur a l'enregistrement" << endl;

}

void classement::charger(string nom_fich){

	ifstream fichier(nom_fich.c_str(), ios::in);
	if(fichier){
		fichier >> taille;
		T = new team[taille];
		M = new match[(taille/2)*((taille-1)*2)];
		for(int i = 0; i < taille; i++){

			fichier >> T[i].nom;
			fichier >> T[i].points;
			fichier >> T[i].joues;
			fichier >> T[i].gagnes;
			fichier >> T[i].nuls;
			fichier >> T[i].perdus;
			fichier >> T[i].bpour;
			fichier >> T[i].bcontre;
			fichier >> T[i].diff;

		}
        int match = (taille/2)*((taille-1)*2);
		for(int j = 0; j < match; j++){
            fichier >> M[j].dom;
            fichier >> M[j].ext;
            fichier >> M[j].BD;
            fichier >> M[j].BE;
            fichier >> M[j].journee;
        }
	}
	else cerr << "Erreur de chargement" << endl;
}

void classement::exporter(){

	string nom_fich;
	cout << "Entrez le nom du fichier à creer sans extension :" << endl;
	cin >> nom_fich;
	ofstream sauve((nom_fich+".csv").c_str(), ios::out);
	if(sauve){
		for(int i = 0; i < taille; i++){
                sauve << T[i].nom << '|';
		        sauve << T[i].points << '|';
		        sauve << T[i].joues << '|';
		        sauve << T[i].gagnes << '|';
		        sauve << T[i].nuls << '|';
        		sauve << T[i].perdus << '|';
        		sauve << T[i].bpour << '|';
        		sauve << T[i].bcontre << '|';
        		sauve << T[i].diff << '|';
       			sauve << endl;

		}
	}
	else cerr << "Erreur a l'exportation" << endl;

}

void classement::html(){

	string nom_fich;
	cout << "Entrez le nom du fichier à creer sans extension :" << endl;
	cin >> nom_fich;
	ofstream sauve((nom_fich+".html").c_str(), ios::out);
	if(sauve){
	    sauve << "<table>" << endl;
		for(int i = 0; i < taille; i++){
                sauve << "<tr>" << endl << "<td>";
                sauve << T[i].nom << "</td>" << endl << "<td>";
		        sauve << T[i].points << "</td>" << endl << "<td>";
		        sauve << T[i].joues << "</td>" << endl << "<td>";
		        sauve << T[i].gagnes << "</td>" << endl << "<td>";
		        sauve << T[i].nuls << "</td>" << endl << "<td>";
        		sauve << T[i].perdus << "</td>" << endl << "<td>";
        		sauve << T[i].bpour << "</td>" << endl << "<td>";
        		sauve << T[i].bcontre << "</td>" << endl << "<td>";
        		sauve << T[i].diff << "</td>" << endl << "</tr>";

		}
		sauve << endl << "</table>";
	}
	else cerr << "Erreur a l'enregistrement" << endl;

}

void classement::menu(){

    int choix = 0;
    bool ok = true;
    while(ok){
        cout << "Quelle operation effectuer ?" << endl;
        cout << "1 - Afficher le classement" << endl;
        cout << "2 - Actualiser le classement" << endl;
        cout << "3 - Enregistrer le classement" << endl;
        cout << "4 - Exporter le classement au format csv" << endl;
        cout << "5 - Exporter le classement au format html" << endl;
        cout << "6 - Afficher les matchs" << endl;
        cout << "7 - Quitter" << endl;

        cin >> choix;

        if(choix == 1) afficher_v2();
        else if(choix == 2) actualiser_v2();
        else if(choix == 3) enregistrer();
        else if(choix == 4) exporter();
        else if(choix == 5) html();
        else if(choix == 6) planing(3);
        else ok = false;
    }
}
