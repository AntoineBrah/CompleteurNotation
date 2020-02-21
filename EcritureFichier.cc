#include "EcritureFichier.h"

ecritureFichier::ecritureFichier(string s){

    const string path = "Interface/cellules.json";
    monFlux.open(path.c_str(), ios::app);

    // Si le flux est bien ouvert
    if(monFlux){
        monFlux << s;
    }
    else{
        cout << "Erreur : l'ouverture en écriture a échouée." << endl;
    }

}

ecritureFichier::~ecritureFichier(){
    monFlux.close();
}

void viderFichier(){

    const string path = "Interface/cellules.json";
    ofstream monFlux;
    monFlux.open(path.c_str());

    monFlux << "[";
    monFlux.close();
}

void correctionSyntaxe(){

    const string path = "Interface/cellules.json";
    ifstream monFluxLecture;
    monFluxLecture.open(path.c_str());

    string json = "";

    string ligne;

    while(getline(monFluxLecture, ligne)){
        json += ligne;
    }

    json.pop_back();
    json += "]";

    ofstream monFluxEcriture;
    monFluxEcriture.open(path.c_str());

    monFluxEcriture << json;

    monFluxLecture.close();
    monFluxEcriture.close();
}
