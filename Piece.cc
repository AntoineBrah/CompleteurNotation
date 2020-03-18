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

string Piece::toString() const{
	return "Type pièce : " + getNomString() + "\nCouleur pièce : " + getCouleur() + "\nPosition pièce : " + getPositionString();
}

Piece::~Piece(){}

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

void updateListeCoupsPossiblesAll(bool lcpCellToo){
	for(Piece *p : getListePiece()){
		p->updateListeCoupsPossibles();

		if(lcpCellToo){
			// On récupère la dernière cellule de la pièce et on la met à jour
			getDernierCSP(p->getFirstCell())->updateListeCoupsPossibles();
		}
	}
}