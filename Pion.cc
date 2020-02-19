#include "Pion.h"

// La prise en passant n'est pour le moment pas opérationnelle

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

    /*
    * On est obligé de vérifier que le pion est toujours dans l'échiquier...
    * Exemple : si on prendre le pion en a2 augmenter x de :
    *               1 = a3 ok, 2 = a4 ok;
    * augmenter x de 1 et y de :
    *       1 = b3 ok,
    * mais augmenter x de 1 et diminuer y de 1 (diagonale gauche) :
    *       on passe de (a2) --> (a0) ERREUR
    * a0 n'est pas défini dans l'échiquier, d'ou la nécessité 
    * d'effectuer des vérifications. 
    */

    // Tout pion peut avancer 2 cases (col+2) devant lui s'il n'a jamais bougé
    // On vérifie que le Pion n'a jamais bougé
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucun Pion n'est présent sur la case col+1
    // Puis on vérifie également qu'aucun pion n'est présent sur la case col+2
    if(!aBouge){        
        if(estCorrectPoint(positionPion+Point(2,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(2,0)))) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(1,0)))))
            listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(2,0)));
    }

    // Tout pion peut avancer 1 case (ligne+1) devant lui
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucun Pion n'est présent sur la case ligne+1
    if(estCorrectPoint(positionPion+Point(1,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(1,0)))))
        listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,0)));

    // Tout pion peut avancer en diagonale gauche (col+1,ligne-1) si il y a une pièce de couleur opposé (il le mange donc)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'un Pion est présent sur la case (col+1, ligne-1)
    // On vérifie que le Pion est de couleur opposé
    if(estCorrectPoint(positionPion+Point(1,-1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,-1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,-1)))->getCouleur() != this->getCouleur())
        listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,-1)));

    // Tout pion peut avancer en diagonale droite (col+1,ligne+1) si il y a une pièce de couleur opposé (il le mange donc)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'un Pion est présent sur la case (col+1, ligne+1)
    // On vérifie que le Pion est de couleur opposé
    if(estCorrectPoint(positionPion+Point(1,1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,1)))->getCouleur() != this->getCouleur())
        listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,1)));
}

Pion::~Pion(){}