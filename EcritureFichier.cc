#include "EcritureFichier.h"

string plateforme = "";

string path_linux = "ChessCompletor-linux-x64/resources/app/cellules.json";
string path_windows = "ChessCompletor-win-x64/resources/app/cellules.json";
string path_macos = "ChessCompletor-darwin-x64/ChessCompletor.app/Contents/Resources/app/cellules.json";


ecritureFichier::ecritureFichier(const string p, string s) : path(p){

    monFlux.open(path.c_str(), ios::app);

    // Si le flux est bien ouvert
    if(monFlux){
        monFlux << s;
    }
    else{
        cout << "Erreur : l'ouverture en écriture a échouée." << endl;
    }

}

string ecritureFichier::getPath() const{
    return path;
}

ecritureFichier::~ecritureFichier(){
    monFlux.close();
}

void viderFichier(const string path){

    ofstream monFlux;
    monFlux.open(path.c_str());

    monFlux << "[";
    monFlux.close();
}

void correctionSyntaxe(const string path){

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
