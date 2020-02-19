#include "Roi.h"

Roi::Roi(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){
    updateListeCoupsPossibles();
}

void Roi::updateListeCoupsPossibles(){

    listeCoupsPossibles.clear(); // On vide la liste actuelle des coups possibles 

    Position currentPosition(pos);
    Point positionPiece = convertPositionToPoint(currentPosition);

    /*
    * Il faudra toujours vérifier que la position de la pièce
    * est toujours dans l'échiquier. Pour se faire on utilise
    * la fonction 'estCorrectPoint(Point)'.
    */

    /*********************************************************************************************/
    /*********************************************************************************************/
    /* Pour le Roi c'est un peu plus compliqué...      voir 'Probleme/Probleme1/explication.txt' */
    /*********************************************************************************************/
    /* -> D'ou le fait de devoir effectuer de nouvelles vérifications en plus des traditionelles */
    /*********************************************************************************************/
    /*********************************************************************************************/


    // Tout Roi peut se déplacer d'une case vers le haut ↑ (ligne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point haut = positionPiece + Point(1,0);

    if(estCorrectPoint(haut) && (!existePieceSurPosition(convertPointToPosition(haut))) && !posDansLCPAdverse(convertPointToPosition(haut))){
        if(!this->possedePionAdverseEnDiagonaleSup(haut)){
            listeCoupsPossibles.push_back(convertPointToPosition(haut));
        }
    }

    // Tout Roi peut se déplacer d'une case vers la diagonale supérieure droite ➚ (ligne+1, colonne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleSupDroite = positionPiece + Point(1,1);

    if(estCorrectPoint(diagonaleSupDroite) && (!existePieceSurPosition(convertPointToPosition(diagonaleSupDroite))) && !posDansLCPAdverse(convertPointToPosition(diagonaleSupDroite))){
        if(!this->possedePionAdverseEnDiagonaleSup(diagonaleSupDroite)){
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleSupDroite));
        }
    }

    // Tout Roi peut se déplacer d'une case vers la droite → (colonne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point droite = positionPiece + Point(0,1);

    if(estCorrectPoint(droite) && (!existePieceSurPosition(convertPointToPosition(droite))) && !posDansLCPAdverse(convertPointToPosition(droite))){
        if(!this->possedePionAdverseEnDiagonaleSup(droite)){
            listeCoupsPossibles.push_back(convertPointToPosition(droite));
        }
    }

    // Tout Roi peut se déplacer d'une case vers la diagonale inférieure droite ➘ (ligne-1, colonne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleInfDroite = positionPiece + Point(-1,1);

    if(estCorrectPoint(diagonaleInfDroite) && (!existePieceSurPosition(convertPointToPosition(diagonaleInfDroite))) && !posDansLCPAdverse(convertPointToPosition(diagonaleInfDroite))){
        if(!this->possedePionAdverseEnDiagonaleSup(diagonaleInfDroite)){
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleInfDroite));
        }
    }

    // Tout Roi peut se déplacer d'une case vers le bas ↓ (ligne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point bas = positionPiece + Point(-1,0);

    if(estCorrectPoint(bas) && (!existePieceSurPosition(convertPointToPosition(bas))) && !posDansLCPAdverse(convertPointToPosition(bas))){
        if(!this->possedePionAdverseEnDiagonaleSup(bas)){
            listeCoupsPossibles.push_back(convertPointToPosition(bas));
        }
    }

    // Tout Roi peut se déplacer d'une case vers la diagonale inférieure gauche ↙ (ligne-1, colonne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleInfGauche = positionPiece + Point(-1,-1);

    if(estCorrectPoint(diagonaleInfGauche) && (!existePieceSurPosition(convertPointToPosition(diagonaleInfGauche))) && !posDansLCPAdverse(convertPointToPosition(diagonaleInfGauche))){
        if(!this->possedePionAdverseEnDiagonaleSup(diagonaleInfGauche)){
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleInfGauche));
        }
    }

    // Tout Roi peut se déplacer d'une case vers la gauche ← (colonne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point gauche = positionPiece + Point(0,-1);

    if(estCorrectPoint(gauche) && (!existePieceSurPosition(convertPointToPosition(gauche))) && !posDansLCPAdverse(convertPointToPosition(gauche))){
        if(!this->possedePionAdverseEnDiagonaleSup(gauche)){
            listeCoupsPossibles.push_back(convertPointToPosition(gauche));
        }
    }

    // Tout Roi peut se déplacer d'une case vers la diagonale supérieure gauche ↖ (ligne+1, colonne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleSupGauche = positionPiece + Point(1,-1);

    if(estCorrectPoint(diagonaleSupGauche) && (!existePieceSurPosition(convertPointToPosition(diagonaleSupGauche))) && !posDansLCPAdverse(convertPointToPosition(diagonaleSupGauche))){
        if(!this->possedePionAdverseEnDiagonaleSup(diagonaleSupGauche)){
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleSupGauche));
        }
    }
}


/*
* On vérifie que la position ou souhaite allez le Roi est dans aucune listePositionPiece de 
* toutes les pièces adverses.
*/
bool Roi::posDansLCPAdverse(const string &p) const{

    for(unsigned int i=0; i<getListePiece()->size(); i++){
        for(unsigned int j=0; j<getListePiece()->at(i)->getListeCoupsPossibles()->size(); j++){
            if((p == getListePiece()->at(i)->getListeCoupsPossibles()->at(j).getCoord()) && (this->getCouleur() != getListePiece()->at(i)->getCouleur())){
                return true;
            }
        }
    }
    return false;
}

bool Roi::possedePionAdverseEnDiagonaleSup(const Point &p){

    bool diagoSupGauche(false);
    bool diagoSupDroite(false);

    // Diagonale gauche supérieure ↖
    if(estCorrectPoint(p) && existePieceSurPosition(convertPointToPosition(p+Point(1,-1)))){
        if(existePieceSurPosition(convertPointToPosition(p+Point(1,-1)))->getNom() == "Pion" && existePieceSurPosition(convertPointToPosition(p+Point(1,-1)))->getCouleur() != this->getCouleur()){
            // Il existe une pièce et il s'agit d'un Pion adverse
            diagoSupGauche = true;
        }
        else{
            // Il existe une pièce et il ne s'agit pas d'un Pion adverse
            diagoSupGauche = false;
        }
    }
    else{
        // La position n'est pas correcte OU il n'existe pas de pièce sur cette position
        diagoSupGauche = false;
    }

    // Diagonale droite supérieure ➚
    if(estCorrectPoint(p) && existePieceSurPosition(convertPointToPosition(p+Point(1,1)))){
        if(existePieceSurPosition(convertPointToPosition(p+Point(1,1)))->getNom() == "Pion" && existePieceSurPosition(convertPointToPosition(p+Point(1,1)))->getCouleur() != this->getCouleur()){
            // Il existe une pièce et il s'agit d'un Pion adverse
            diagoSupDroite = true;
        }
        else{
            // Il existe une pièce et il ne s'agit pas d'un Pion adverse
            diagoSupDroite = false;
        }
    }
    else{
        // La position n'est pas correcte OU il n'existe pas de pièce sur cette position
        diagoSupDroite = false;
    }

    return diagoSupGauche || diagoSupDroite;
}

Roi::~Roi(){}