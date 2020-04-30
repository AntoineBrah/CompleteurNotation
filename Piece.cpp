#include "Piece.h"
#include "Cellule.h"

Piece::Piece() : couleur(Null), nom(type::Null), pos(""), aBouge(false), firstCell(NULL){}
Piece::Piece(Couleur c, type::Nom n, string p) : couleur(c), nom(n), pos(p), aBouge(false), firstCell(NULL){
	listePiece.push_back(this);
}

string Piece::getCouleur() const{
	switch(couleur){
		case Blanc : 
			return "Blanc";
			break;
		case Noir : 
			return "Noir";
			break;
		default:
			return "Null";
			break;
	}
}

type::Nom Piece::getNom() const{
	return nom;
}

string Piece::getNomString() const{
	switch(nom){
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
			return "Erreur";
			break;
	}
}

Position Piece::getPosition() const{
	return pos;
}

string Piece::getPositionString() const{
	return pos.getCoord();
}

bool Piece::getABouge() const{
	return aBouge;
}

Cellule* Piece::getFirstCell() const{
	return firstCell;
}

void Piece::setFirstCell(Cellule* c){
	firstCell = c;
}

void Piece::setPostion(string position){

	pos.setCoord(position);

	if(!aBouge)
		aBouge = true;
}

void Piece::setNom(string typePiece){
	
	switch(typePiece[1]){
		case 'D':
			nom = type::Dame;
			break;
		case 'C':
			nom = type::Cavalier;
			break;
		case 'T':
			nom = type::Tour;
			break;
		case 'F':
			nom = type::Fou;
			break;
	}
	
}

vector<Position>& Piece::getListeCoupsPossibles(){
	return listeCoupsPossibles;
}

void Piece::printListeCoupsPossibles() const{

	cout << "{";

	if(listeCoupsPossibles.size() > 0){ // car erreur compilation si la liste est vide
		for(unsigned int i=0; i<=listeCoupsPossibles.size()-1; i++){

			if(i==listeCoupsPossibles.size()-1){
				cout << listeCoupsPossibles.at(i).getCoord();
			}
			else{
				cout << listeCoupsPossibles.at(i).getCoord() << ",";
			}
		}
	}

	cout << "}" << endl;
}

void Piece::supprimePosDeLCP(const Position& pos){

	int i=0;

	for(Position p : listeCoupsPossibles){
		if(pos.getCoord() == p.getCoord()){
			listeCoupsPossibles.erase(listeCoupsPossibles.begin() + i);   
		}

		i++;
	}
}


string Piece::toString() const{

  ostringstream adrPiece, adrFirstCell;

  adrPiece << this;
  adrFirstCell << this->getFirstCell();

	return "Pièce :\n\t- Adr pièce : " + adrPiece.str() + "\n\t- Adr firstCell : " + adrFirstCell.str() + "\n\t- Type pièce : " + this->getNomString() + "\n\t- Couleur : " + this->getCouleur() + "\n\t- Position : " + this->getPositionString();
}

Piece::~Piece(){

	int cpt = 0;

    for(Piece* p : listePiece){
        
        if(p == this){
            listePiece.erase(listePiece.begin()+cpt);
        }

        cpt++;
    }
}

Piece* existePieceSurPosition(string p){
	for(Piece *piece : listePiece){
		if(piece->getPosition().getCoord() == p){
			return piece;
		}
	}
	return NULL;
}

vector<Piece*>& getListePiece(){
	return listePiece;
}

bool appartientLCP(Piece* p, string position){

	for(Position pos : p->getListeCoupsPossibles()){
		if(pos.getCoord() == position){
			return true;
		}
	}

	return false;
}

void updateListeCoupsPossiblesAll(bool lcpCellToo){

	for(Piece *p : getListePiece()){

		p->updateListeCoupsPossibles();

		if(lcpCellToo){
			// On récupère la dernière cellule de la pièce et on la met à jour
			getDernierCSP(p->getFirstCell())->updateListeCoupsPossibles();
		}
	}

}