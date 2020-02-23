#include "Roi.h"

Roi::Roi(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){}

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
    /*               - n'est pas dans liste des coups possibles d'une pièce adverse (LCPA)       */
    /*               - la case ou le Roi souhaite aller ne possede pas de Pion adverse sur les   */
    /*                 diagonales supérieures 'possedePionEnDiagonalSup'...                      */
    /*********************************************************************************************/
    /*********************************************************************************************/


    // Tout Roi peut se déplacer d'une case vers le haut ↑ (ligne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point haut = positionPiece + Point(1,0);
    
    if(estCorrectPoint(haut) && !posDansLCPAdverse(convertPointToPosition(haut)) && !this->possedePionAdverseEnDiagonaleSup(haut)){
        if(existePieceSurPosition(convertPointToPosition(haut))){
            if(existePieceSurPosition(convertPointToPosition(haut))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(haut));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(haut));
        }
    }
    
    

    // Tout Roi peut se déplacer d'une case vers la diagonale supérieure droite ➚ (ligne+1, colonne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleSupDroite = positionPiece + Point(1,1);
    
    if(estCorrectPoint(diagonaleSupDroite) && !posDansLCPAdverse(convertPointToPosition(diagonaleSupDroite)) && !this->possedePionAdverseEnDiagonaleSup(diagonaleSupDroite)){
        if(existePieceSurPosition(convertPointToPosition(diagonaleSupDroite))){
            if(existePieceSurPosition(convertPointToPosition(diagonaleSupDroite))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(diagonaleSupDroite));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleSupDroite));
        }
    }
    
    

    // Tout Roi peut se déplacer d'une case vers la droite → (colonne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point droite = positionPiece + Point(0,1);
    
    if(estCorrectPoint(droite) && !posDansLCPAdverse(convertPointToPosition(droite)) && !this->possedePionAdverseEnDiagonaleSup(droite)){
        if(existePieceSurPosition(convertPointToPosition(droite))){
            if(existePieceSurPosition(convertPointToPosition(droite))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(droite));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(droite));
        }
    }
    

    // Tout Roi peut se déplacer d'une case vers la diagonale inférieure droite ➘ (ligne-1, colonne+1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleInfDroite = positionPiece + Point(-1,1);
    
    if(estCorrectPoint(diagonaleInfDroite) && !posDansLCPAdverse(convertPointToPosition(diagonaleInfDroite)) && !this->possedePionAdverseEnDiagonaleSup(diagonaleInfDroite)){
        if(existePieceSurPosition(convertPointToPosition(diagonaleInfDroite))){
            if(existePieceSurPosition(convertPointToPosition(diagonaleInfDroite))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(diagonaleInfDroite));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleInfDroite));
        }
    }
    

    // Tout Roi peut se déplacer d'une case vers le bas ↓ (ligne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point bas = positionPiece + Point(-1,0);
    
    if(estCorrectPoint(bas) && !posDansLCPAdverse(convertPointToPosition(bas)) && !this->possedePionAdverseEnDiagonaleSup(bas)){
        if(existePieceSurPosition(convertPointToPosition(bas))){
            if(existePieceSurPosition(convertPointToPosition(bas))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(bas));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(bas));
        }
    }
    

    // Tout Roi peut se déplacer d'une case vers la diagonale inférieure gauche ↙ (ligne-1, colonne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleInfGauche = positionPiece + Point(-1,-1);
    
    if(estCorrectPoint(diagonaleInfGauche) && !posDansLCPAdverse(convertPointToPosition(diagonaleInfGauche)) && !this->possedePionAdverseEnDiagonaleSup(diagonaleInfGauche)){
        if(existePieceSurPosition(convertPointToPosition(diagonaleInfGauche))){
            if(existePieceSurPosition(convertPointToPosition(diagonaleInfGauche))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(diagonaleInfGauche));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleInfGauche));
        }
    }
    

    // Tout Roi peut se déplacer d'une case vers la gauche ← (colonne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)

    Point gauche = positionPiece + Point(0,-1);
    
    if(estCorrectPoint(gauche) && !posDansLCPAdverse(convertPointToPosition(gauche)) && !this->possedePionAdverseEnDiagonaleSup(gauche)){
        if(existePieceSurPosition(convertPointToPosition(gauche))){
            if(existePieceSurPosition(convertPointToPosition(gauche))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(gauche));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(gauche));
        }
    }
    
    

    // Tout Roi peut se déplacer d'une case vers la diagonale supérieure gauche ↖ (ligne+1, colonne-1)
    // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
    // On vérifie qu'aucune Pièce n'est présente sur la case
    // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
    // On effectue les vérifications du Problème1 (Problème entre Roi et Pion adverse)
    Point diagonaleSupGauche = positionPiece + Point(1,-1);
    
    if(estCorrectPoint(diagonaleSupGauche) && !posDansLCPAdverse(convertPointToPosition(diagonaleSupGauche)) && !this->possedePionAdverseEnDiagonaleSup(diagonaleSupGauche)){
        if(existePieceSurPosition(convertPointToPosition(diagonaleSupGauche))){
            if(existePieceSurPosition(convertPointToPosition(diagonaleSupGauche))->getCouleur() != this->getCouleur()){
                listeCoupsPossibles.push_back(convertPointToPosition(diagonaleSupGauche));
            }
        }
        else{
            listeCoupsPossibles.push_back(convertPointToPosition(diagonaleSupGauche));
        }
    }
    
    
}


/*
* On vérifie que la position ou souhaite allez le Roi est dans aucune listeCoupsPossibles de 
* toutes les pièces adverses.
*/
bool Roi::posDansLCPAdverse(const string &position) const{
    for(Piece *p : getListePiece()){
        if(p->getCouleur() != this->getCouleur() && p->getNom() != "Pion"){
            for(Position pos : p->getListeCoupsPossibles()){
                if(position == pos.getCoord()){
                    // On vérifie la liste des coups possibles de la pièce
                    // Que la pièce est bien de couleur opposée
                    // Qu'il ne s'agit d'un Pion (car un Pion n'est pas une menace pour le Roi dans sa liste des coups possibles)
                    return true;
                }
            }
        }
    }
    return false;
}

bool Roi::possedePionAdverseEnDiagonaleSup(const Point &p){

    bool diagoSupGauche(false);
    bool diagoSupDroite(false);

    // Diagonale gauche supérieure ↖
    if(estCorrectPoint(p) && estCorrectPoint(p+Point(1,-1)) && existePieceSurPosition(convertPointToPosition(p+Point(1,-1)))){
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
    if(estCorrectPoint(p) && estCorrectPoint(p+Point(1,1)) && existePieceSurPosition(convertPointToPosition(p+Point(1,1)))){
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