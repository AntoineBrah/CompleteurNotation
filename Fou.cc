#include "Fou.h"

Fou::Fou(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){}

void Fou::updateListeCoupsPossibles(){

    listeCoupsPossibles.clear(); // On vide la liste actuelle des coups possibles 

    if(this->getPositionString() != "NULL"){

        Position currentPosition(pos);
        Point positionPiece = convertPositionToPoint(currentPosition);

        /*
        * Il faudra toujours vérifier que la position de la pièce
        * est toujours dans l'échiquier. Pour se faire on utilise
        * la fonction 'estCorrectPoint(Point)'.
        */
    

        // Tout Fou peut se déplacer en diagonale haut/droit ➚ (ligne➚ et colonne➚)
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

        // Tout Fou peut se déplacer en diagonale bas/droit ➘ (ligne➘ et colonne➚)
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

        // Tout Fou peut se déplacer en diagonale bas/gauche ↙ (ligne➘ et colonne➘)
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

        // Tout Fou peut se déplacer en diagonale haut/gauche ↖ (ligne➚ et colonne➘)
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

Fou::~Fou(){}