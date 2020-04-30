#include "Dame.h"

int Dame::nbInstances = 0;

Dame::Dame(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){
    nbInstances++;
}

void Dame::updateListeCoupsPossibles(){

    listeCoupsPossibles.clear(); // On vide la liste actuelle des coups possibles 

    if(this->getPositionString() != "NULL"){

        Position currentPosition(pos);
        Point positionPiece = convertPositionToPoint(currentPosition);

        /*
        * Il faudra toujours vérifier que la position de la pièce
        * est toujours dans l'échiquier. Pour se faire on utilise
        * la fonction 'estCorrectPoint(Point)'.
        */

        /*************************/
        /** Déplacement en Tour **/
        /*************************/

        // Toute Dame peut se déplacer en vers le haut ↑ (ligne)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        for(int x=positionPiece.getX()+1; x<=8; x++){
            if(estCorrectPoint(Point(x,positionPiece.getY()))){
                if(existePieceSurPosition(convertPointToPosition(Point(x,positionPiece.getY())))){
                    if(existePieceSurPosition(convertPointToPosition(Point(x,positionPiece.getY())))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(x,positionPiece.getY())));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(x,positionPiece.getY())));
                }
            }
        }

        // Toute Dame peut se déplacer en vers la droite → (colonne)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        for(int y=positionPiece.getY()+1; y<=8; y++){
            if(estCorrectPoint(Point(positionPiece.getX(),y))){
                if(existePieceSurPosition(convertPointToPosition(Point(positionPiece.getX(),y)))){
                    if(existePieceSurPosition(convertPointToPosition(Point(positionPiece.getX(),y)))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(positionPiece.getX(),y)));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(positionPiece.getX(),y)));
                }
            }
        }

        // Toute Dame peut se déplacer en vers le bas ↓ (ligne)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        for(int x=positionPiece.getX()-1; x>=1; x--){
            if(estCorrectPoint(Point(x,positionPiece.getY()))){
                if(existePieceSurPosition(convertPointToPosition(Point(x,positionPiece.getY())))){
                    if(existePieceSurPosition(convertPointToPosition(Point(x,positionPiece.getY())))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(x,positionPiece.getY())));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(x,positionPiece.getY())));
                }
            }
        }

        // Toute Dame peut se déplacer en vers la droite ← (colonne)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        for(int y=positionPiece.getY()-1; y>=1; y--){
            if(estCorrectPoint(Point(positionPiece.getX(),y))){
                if(existePieceSurPosition(convertPointToPosition(Point(positionPiece.getX(),y)))){
                    if(existePieceSurPosition(convertPointToPosition(Point(positionPiece.getX(),y)))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(positionPiece.getX(),y)));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(positionPiece.getX(),y)));
                }
            }
        }

        /************************/
        /** Déplacement en Fou **/
        /************************/

        // Toute Dame peut se déplacer en diagonale haut/droit ➚ (ligne➚ et colonne➚)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée

        int x = positionPiece.getX()+1;
        int y = positionPiece.getY()+1;

        while(x<=8 && y<=8){
            if(estCorrectPoint(Point(x,y))){
                if(existePieceSurPosition(convertPointToPosition(Point(x,y)))){
                    if(existePieceSurPosition(convertPointToPosition(Point(x,y)))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                    x++;
                    y++;
                }
            }
            else{
                break;
            }
        }

        // Toute Dame peut se déplacer en diagonale bas/droit ➘ (ligne➘ et colonne➚)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée
        
        x = positionPiece.getX()-1;
        y = positionPiece.getY()+1;


        while(x>=1 && y<=8){
            if(estCorrectPoint(Point(x,y))){
                if(existePieceSurPosition(convertPointToPosition(Point(x,y)))){
                    if(existePieceSurPosition(convertPointToPosition(Point(x,y)))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                    x--;
                    y++;
                }
            }
            else{
                break;
            }
        }

        // Toute Dame peut se déplacer en diagonale bas/gauche ↙ (ligne➘ et colonne➘)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée

        x = positionPiece.getX()-1;
        y = positionPiece.getY()-1;

        while(x>=1 && y>=1){
            if(estCorrectPoint(Point(x,y))){
                if(existePieceSurPosition(convertPointToPosition(Point(x,y)))){
                    if(existePieceSurPosition(convertPointToPosition(Point(x,y)))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                    x--;
                    y--;
                }
            }
            else{
                break;
            }
        }

        // Toute Dame peut se déplacer en diagonale haut/gauche ↖ (ligne➚ et colonne➘)
        // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
        // On vérifie qu'aucune Pièce n'est présente sur la case
        // Si une Pièce et présente, on vérifie qu'elle est de couleur opposée

        x = positionPiece.getX()+1;
        y = positionPiece.getY()-1;

        while(x<=8 && y>=1){
            if(estCorrectPoint(Point(x,y))){
                if(existePieceSurPosition(convertPointToPosition(Point(x,y)))){
                    if(existePieceSurPosition(convertPointToPosition(Point(x,y)))->getCouleur() != this->getCouleur()){
                        listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                        break;
                    }
                    else{
                        break;
                    }
                }
                else{
                    listeCoupsPossibles.push_back(convertPointToPosition(Point(x,y)));
                    x++;
                    y--;
                }
            }
            else{
                break;
            }
        }
    }


    
}

Dame::~Dame(){}