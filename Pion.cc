#include "Pion.h"

/*
* Potentiel problème avec le 'aBouge' qui est initialisé à false
* dès qu'on créé une pièce. Car si on part sur une création de pièce
* non reliée à sa liste CoupSuivantPièce, la pièce a donc déjà été
* déplacé mais elle est instancier avec une valeur 'false' pour son
* attribut 'aBouge'... 
* Réfléchir à ce problème lors de l'implétation de la gestion des 
* erreurs;
*/

Pion::Pion(Couleur c, type::Nom n, string pos) : Piece(c,n,pos), aBouge(false){
    updateListeCoupsPossibles();
}

void Pion::updateListeCoupsPossibles(){

    listeCoupsPossibles.clear(); // On vide la liste actuelle des coups possibles 

    Position currentPosition(pos);

    Point positionPion = convertPositionToPoint(currentPosition);

    if(aBouge){
        Point positionsPossibles(positionPion);

        // Tout pion peut avancer 1 case devant lui
        positionsPossibles.setY(positionsPossibles.getY()+1);

        listeCoupsPossibles.push_back(convertPointToPosition(positionsPossibles));

        // Tout pion peut avancer en diagonale gauche 
        positionsPossibles = positionPion;

        positionsPossibles.setY(positionsPossibles.getY()+1);
        positionsPossibles.setX(positionsPossibles.getX()-1);
        
        listeCoupsPossibles.push_back(convertPointToPosition(positionsPossibles));

        // Tout pion peut avancer en diagonale droite
        positionsPossibles = positionPion;

        positionsPossibles.setY(positionsPossibles.getY()+1);
        positionsPossibles.setX(positionsPossibles.getX()+1);

        listeCoupsPossibles.push_back(convertPointToPosition(positionsPossibles));
    }
    else{
        aBouge = false;

        Point positionsPossibles(positionPion);

        // Tout pion peut avancer 2 cases devant lui
        positionsPossibles.setX(positionsPossibles.getX()+2);

        listeCoupsPossibles.push_back(convertPointToPosition(positionsPossibles));

        // Tout pion peut avancer 1 case devant lui
        positionsPossibles = positionPion;
        positionsPossibles.setX(positionsPossibles.getX()+1);

        listeCoupsPossibles.push_back(convertPointToPosition(positionsPossibles));

        // Tout pion peut avancer en diagonale gauche 
        positionsPossibles = positionPion;

        positionsPossibles.setX(positionsPossibles.getX()+1);
        positionsPossibles.setY(positionsPossibles.getY()-1);
        
        listeCoupsPossibles.push_back(convertPointToPosition(positionsPossibles));

        // Tout pion peut avancer en diagonale droite
        positionsPossibles = positionPion;

        positionsPossibles.setX(positionsPossibles.getX()+1);
        positionsPossibles.setY(positionsPossibles.getY()+1);

        listeCoupsPossibles.push_back(convertPointToPosition(positionsPossibles));
    }
}




Pion::~Pion(){}