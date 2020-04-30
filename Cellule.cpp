#include "Cellule.h"

unsigned int Cellule::nbErreur = 0; // On initialise l'attribut de classe à 0

Cellule::Cellule() : piece(NULL), CSP(NULL), CPP(NULL), CSE(NULL), CPE(NULL), type(type::Null), pos("NULL"), certitude(Incertain){
  listeCellule.push_back(this);
}

Cellule::Cellule(Piece* p) : piece(p), CSP(NULL), CPP(NULL), CSE(NULL), CPE(NULL), type(p->getNom()), pos(p->getPositionString()), certitude(Vrai){
    listeCellule.push_back(this);
}

Piece* Cellule::getPiece(){
    return piece;
}

Cellule* Cellule::getCSP() const{
    return CSP;
}

Cellule* Cellule::getCPP() const{
    return CPP;
}

Cellule* Cellule::getCSE() const{
    return CSE;
}

Cellule* Cellule::getCPE() const{
    return CPE;
}

vector<vector<Position> >& Cellule::getListeCoupsPossibles(){
    return listeCoupsPossibles;
}

void Cellule::copieListeCoupsPossibles(Cellule *c){
    if(c != NULL){
        for(vector<Position> vect : c->getListeCoupsPossibles()){
            listeCoupsPossibles.push_back(vect);
        }
    }
}

void Cellule::updateListeCoupsPossibles(){
    // On ajoute le vector de la liste des coups possibles de la pièce vers laquelle la cellule pointe
    listeCoupsPossibles.push_back(piece->getListeCoupsPossibles());
}

Position Cellule::getPositionCell() const{
    return pos;
}

string Cellule::getPosition() const{
    return pos.getCoord();
}

string Cellule::getTypePiece() const{
    switch(type){
		case type::Pion : 
			return "Pion";
			break;
		case type::Tour : 
			return "Tour";
			break;
		case type::Cavalier : 
			return "Cavalier";
			break;
		case type::Fou : 
			return "Fou";
			break;
		case type::Dame : 
			return "Dame";
			break;
		case type::Roi : 
			return "Roi";
			break;
		default:
			return "NULL";
			break;
	}
}

string Cellule::getVeracite() const{
    switch(certitude){
        case Vrai:
            return "Vrai";
            break;
        case Incertain:
            return "Incertain";
            break;
        case Faux:
            return "Faux";
            break;
        default:
            return "NULL"; // Ça n'arrive jamais
            break;
    }
}

string Cellule::toString() const{

  string toStringPiece = "";

  if(piece != NULL){

    ostringstream adrPiece, adrFirstCell;

    adrPiece << piece;
    adrFirstCell << piece->getFirstCell();

    toStringPiece = "- Adr pièce : " + adrPiece.str() + "\n\t\t- Adr firstCell : " + adrFirstCell.str() + "\n\t\t- Type pièce : " + piece->getNomString() + "\n\t\t- Couleur : " + piece->getCouleur() + "\n\t\t- Position : " + piece->getPositionString();
  }
  else{
    toStringPiece = "NULL (Cellule vide)";
  }

    ostringstream adr, piece, csp, cpp, cse, cpe;

    adr << this;
    csp << CSP;
    cpp << CPP;
    cse << CSE;
    cpe << CPE;


  return "Cellule :\n\t- Adr : " + adr.str() + "\n\t- CSP : " + csp.str() + "\n\t- CPP : " + cpp.str() + "\n\t- CSE : " + cse.str() + "\n\t- CPE : " + cpe.str() + "\n\t- Position : " + getPosition() + "\n\t- Type : " + getTypePiece() + "\n\t- Veracité : " + getVeracite() + "\n\t- Pointeur vers pièce : \n\t\t" + toStringPiece; 
}

string Cellule::getJSON() const{

    ostringstream adrCSP, adrCPP, adrCSE, adrCPE, instanceCourante;
    adrCSP << CSP;
    adrCPP << CPP;
    adrCSE << CSE;
    adrCPE << CPE;
    instanceCourante << this;

    string couleurPiece = "";

    if(piece){
      couleurPiece = piece->getCouleur();
    }
    else{
      couleurPiece = "NULL";
    }

    string json = "{\"adr\":\"" + instanceCourante.str() + "\",";
    json += "\"cpp\":\"" + adrCPP.str() + "\",";
    json += "\"csp\":\"" + adrCSP.str() + "\",";
    json += "\"cse\":\"" + adrCSE.str() + "\",";
    json += "\"cpe\":\"" + adrCPE.str() + "\",";
    json += "\"piece\":\"" + getTypePiece() + "\",";
    json += "\"couleur\":\"" + couleurPiece + "\",";
    json += "\"position\":\"" + pos.getCoord() + "\",";
    json += "\"lcp\":\""; 

    if(!listeCoupsPossibles.empty()){
        for(unsigned int i=0; i<listeCoupsPossibles.size(); i++){
            if(!listeCoupsPossibles.at(i).empty()){
                if(i != listeCoupsPossibles.size()-1){
                    for(unsigned int j=0; j<listeCoupsPossibles.at(i).size(); j++){
                        if(j != listeCoupsPossibles.at(i).size()-1){
                            json += listeCoupsPossibles.at(i).at(j).getCoord() + " ";
                        }
                        else{
                            json += listeCoupsPossibles.at(i).at(j).getCoord();
                        }
                    }
                    json += ",";
                }
                else{
                   for(unsigned int j=0; j<listeCoupsPossibles.at(i).size(); j++){
                        if(j != listeCoupsPossibles.at(i).size()-1){
                            json += listeCoupsPossibles.at(i).at(j).getCoord() + " ";
                        }
                        else{
                            json += listeCoupsPossibles.at(i).at(j).getCoord();
                        }
                    } 
                }
            }
            else{
                if(i != listeCoupsPossibles.size()-1)
                    json += ",";
            }
        }
    }

    json += "\"}";

    return json;
}


void Cellule::setPiece(Piece *p){
    piece = p;
}


void Cellule::setCSP(Cellule *c){
    CSP=c;
}

void Cellule::setCPP(Cellule *c){
    CPP=c;
}

void Cellule::setCSE(Cellule *c){
    CSE=c;
}

void Cellule::setCPE(Cellule *c){
    CPE=c;
}

void Cellule::setVeracite(const Veracite c){
    certitude = c;
}

Cellule::~Cellule(){

    int cpt = 0;

    for(Cellule* cell : listeCellule){
        
        if(cell == this){
            listeCellule.erase(listeCellule.begin()+cpt);
        }

        cpt++;
    }
}

vector<Cellule*>& getListeCellule(){
	return listeCellule;
}

Cellule* getDernierCSP(Cellule* c){

    while(c->getCSP()){
        c=c->getCSP();
    }

    return c;
}


Cellule* getDernierCSE(){
    for(Piece* p : getListePiece()){
        if(p->getFirstCell()->getCSE() != NULL){

            Cellule* c = p->getFirstCell();
            
            while(c->getCSE()){
                c=c->getCSE();
            }
            
            return c;
        }
    }
    return NULL; // Ça n'arrive jamais
}


Cellule* getPremierCSE(){
    for(Piece* p : getListePiece()){
      if(p->getFirstCell()->getCSE() != NULL){
        return p->getFirstCell();
      }
    }

    return NULL; // Ça n'arrive jamais
}

int getStructSize(){

  int nbr = 1;

  Cellule *k = getPremierCSE();

  while(k->getCSE() != NULL){
    nbr++;
    k = k->getCSE();
  }

  return nbr;
}

void backtrackStruct(int nbDeCSE){

  if(getStructSize() <= nbDeCSE){

    cout << "[!] Impossible de revenir " << nbDeCSE << " fois en arrière dans le chainage des cellules car la structure est de taille : " << getStructSize() << endl << endl;

  }else{
    Cellule *k = getDernierCSE();
    int n = nbDeCSE;

    while(n>0){

      Cellule *cpe = k->getCPE();

      k->getPiece()->setPostion(k->getCPP()->getPosition());

      for(Piece *p: getListePiece()){
        Cellule *c = getDernierCSP(p->getFirstCell());

        if(!c->getListeCoupsPossibles().empty()){
          c->getListeCoupsPossibles().pop_back();
        }
      }

      delete k;

      k=cpe;
      n--;
    }
  }
}