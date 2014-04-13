#include <iostream>
using namespace std;

typedef struct team{

	string nom;
	int points;
	int joues;
	int gagnes;
	int nuls;
	int perdus;
	int bpour;
	int bcontre;
	int diff;
}team;

typedef struct match{

    string dom;
    string ext;
    int BD;
    int BE;
    int journee;
}match;

class classement{

	int taille;
	team *T;
	match *M;

	public:

	classement();
	classement(int t);
	classement(string nom_fichier);
	~classement();
    void setTeam(int i, string name);
	void remplir();
	void planifier();
	void dater();

	int longMax();
	void espacer(int nb);
	void afficher_team_v2(int indice);
	void afficher_v2();
	void planing(int type); // 1 avec num <> 0 sans
	void planing_nb();
	void afficher_match(int i);
	void afficher_journee(int jour, int mode);

	bool superieure(int i, int j); //vrai si i>j
	void echanger(int i, int j);
	void tri();
	void actualiser_v2();
	void actualiser_team_v2(int ind, int dom_ext, int BM, int BE);
	void suppr();
	void suppr_match(int i);
	void actualiser_match(int i);

	void charger(string);
	void enregistrer();
	void exporter();
	void html();

	void menu();
};
