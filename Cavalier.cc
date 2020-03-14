#include "Cavalier.h"

Cavalier::Cavalier(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){}

void Cavalier::updateListeCoupsPossibles(){

    listeCoupsPossibles.clear(); // On vide la liste actuelle des coups possibles 

    if(this->getPositionString() != "NULL"){

        Position currentPosition(pos);
        Point positionPiece = convertPositionToPoint(currentPosition);

        /*
        * Il faudra toujours vérifier que la position de la pièce
        * est toujours dans l'échiquier. Pour se faire on utilise
        * la fonction 'estCorrectPoint(Point)'.
        * 
        * Pour expliquer les vérifications, on part de l'hypothèse
        * qu'il existe un Cavalier en d4.
        * 
        * d4 <=> Point(4,4);
        * 
        * A partir de d4, le cavalier est censé pouvoir aller en :
        * e6, f5, f3, e2, c2, b3, b5, c6 sauf s'il y a une pièce
        * de même couleur que le cavalier sur une de ces positions.
        */

        // Tout cavalier peut se déplacer en en L vertical droit : ↑→ (ligne+2, col+1)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne+2, col+1)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        if(estCorrectPoint(positionPiece+Point(2,1))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(2,1)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(2,1)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(2,1)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(2,1)));
            }
        }


        
        // Tout cavalier peut se déplacer en en L vertical droit : →↑ (ligne+1, col+2)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne+1, col+2)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        if(estCorrectPoint(positionPiece+Point(1,2))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(1,2)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(1,2)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(1,2)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(1,2)));
            }
        }



        // Tout cavalier peut se déplacer en en L vertical droit : →↓ (ligne-1, col+2)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne-1, col+2)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        if(estCorrectPoint(positionPiece+Point(-1,2))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-1,2)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-1,2)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-1,2)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-1,2)));
            }
        }



        // Tout cavalier peut se déplacer en en L vertical droit : ↓→ (ligne-2, col+1)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne-2, col+1)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        
        if(estCorrectPoint(positionPiece+Point(-2,1))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-2,1)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-2,1)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-2,1)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-2,1)));
            }
        }
        


        // Tout cavalier peut se déplacer en en L vertical droit : ←↓ (ligne-2, col-1)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne-2, col-1)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        
        if(estCorrectPoint(positionPiece+Point(-2,-1))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-2,-1)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-2,-1)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-2,-1)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-2,-1)));
            }
        }

        // Tout cavalier peut se déplacer en en L vertical droit : ↓← (ligne-1, col-2)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne-1, col-2)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        if(estCorrectPoint(positionPiece+Point(-1,-2))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-1,-2)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(-1,-2)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-1,-2)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(-1,-2)));
            }
        }

        // Tout cavalier peut se déplacer en en L vertical droit : ←↑ (ligne+1, col-2)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne+1, col-2)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        if(estCorrectPoint(positionPiece+Point(1,-2))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(1,-2)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(1,-2)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(1,-2)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(1,-2)));
            }
        }


        // Tout cavalier peut se déplacer en en L vertical droit : ↑← (ligne+2, col-1)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case (ligne+2, col-1)
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        if(estCorrectPoint(positionPiece+Point(2,-1))){
            if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(2,-1)))){
                if(existePieceSurPosition(convertPointToPosition(positionPiece+Point(2,-1)))->getCouleur() != this->getCouleur()){
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(2,-1)));
                }
            }
            else{
                listeCoupsPossibles.push_back(convertPointToPosition(positionPiece+Point(2,-1)));
            }
        }
    }

}

Cavalier::~Cavalier(){}