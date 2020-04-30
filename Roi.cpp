#include "Roi.h"

Roi::Roi(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){}

void Roi::updateListeCoupsPossibles(){

    listeCoupsPossibles.clear(); // On vide la liste actuelle des coups possibles 

    if(this->getPositionString() != "NULL"){

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


        /*
        *   Pour le ROQUE :
        * 
        *  Il faut vérifier que :
        *   - Le Roi et la Tour avec laquelle on souhaite roquer n'aient jamais bougé (1)
        *   - Il n'y ait aucune pièce entre le Roi et la Tour (2)
        *   - Que le Roi ne soit pas en échec (car s'il est en échec il n'a pas le droit de Roquer) (2bis)
        *   - Aucune pièce noir n'a dans sa lcp les cases de Roque du Roi (car sinon ça interdit le Roque) (3)
        *   - Gérer le fait que ça soit un Pion adverse (3bis)
        */


        /*********************/
        /* ROQUE : ROI BLANC */
        /*********************/

        if(this->getCouleur() == "Blanc"){

            // Petit roque (1) et (2)
            if(this->getABouge() == false && !existePieceSurPosition("f1") && !existePieceSurPosition("g1") && existePieceSurPosition("h1") && existePieceSurPosition("h1")->getCouleur() == "Blanc" && existePieceSurPosition("h1")->getNomString() == "Tour" && existePieceSurPosition("h1")->getABouge() == false){
                //(2bis) et (3) : On regarde qu'aucune pièce adverse vise f1 et g1
                if(!estEnEchecRoi("Blanc") && !this->posDansLCPAdverse("f1") && !this->posDansLCPAdverse("g1") && !this->possedePionAdverseEnDiagonaleSup(Point(1,6)) &&!this->possedePionAdverseEnDiagonaleSup(Point(1,7))){
                    listeCoupsPossibles.push_back(Position("g1")); // Case du petit roque
                }
            }

            // Grand roque (1) et (2)
            if(this->getABouge() == false && !existePieceSurPosition("b1") && !existePieceSurPosition("c1") && !existePieceSurPosition("d1") && existePieceSurPosition("a1") && existePieceSurPosition("a1")->getCouleur() == "Blanc" && existePieceSurPosition("a1")->getNomString() == "Tour" && existePieceSurPosition("a1")->getABouge() == false){
                //(2bis) et (3) : On regarde qu'aucune pièce adverse vise b1 et c1 et d1
                if(!estEnEchecRoi("Blanc") && !this->posDansLCPAdverse("b1") && !this->posDansLCPAdverse("c1") && !this->posDansLCPAdverse("d1") && !this->possedePionAdverseEnDiagonaleSup(Point(1,2)) && !this->possedePionAdverseEnDiagonaleSup(Point(1,3)) && !this->possedePionAdverseEnDiagonaleSup(Point(1,4))){
                    listeCoupsPossibles.push_back(Position("c1")); // Case du grand roque
                }
            }
            
        }



        /********************/
        /* ROQUE : ROI NOIR */
        /********************/

        if(this->getCouleur() == "Noir"){

            // Petit roque (1) et (2)
            if(this->getABouge() == false && !existePieceSurPosition("f8") && !existePieceSurPosition("g8") && existePieceSurPosition("h8") && existePieceSurPosition("h8")->getCouleur() == "Noir" && existePieceSurPosition("h8")->getNomString() == "Tour" && existePieceSurPosition("h8")->getABouge() == false){
                //(2bis) et (3) : On regarde qu'aucune pièce adverse vise f8 et g8
                if(!estEnEchecRoi("Noir") && !this->posDansLCPAdverse("f8") && !this->posDansLCPAdverse("g8") && !this->possedePionAdverseEnDiagonaleSup(Point(8,6)) &&!this->possedePionAdverseEnDiagonaleSup(Point(8,7))){
                    listeCoupsPossibles.push_back(Position("g8")); // Case du petit roque
                }
            }

            // Grand roque (1) et (2)
            if(this->getABouge() == false && !existePieceSurPosition("b8") && !existePieceSurPosition("c8") && !existePieceSurPosition("d8") && existePieceSurPosition("a8") && existePieceSurPosition("a8")->getCouleur() == "Noir" && existePieceSurPosition("a8")->getNomString() == "Tour" && existePieceSurPosition("a8")->getABouge() == false){
                //(2bis) et (3) : On regarde qu'aucune pièce adverse vise b1 et c1 et d1
                if(!estEnEchecRoi("Noir") && !this->posDansLCPAdverse("b8") && !this->posDansLCPAdverse("c8") && !this->posDansLCPAdverse("d8") && !this->possedePionAdverseEnDiagonaleSup(Point(8,2)) && !this->possedePionAdverseEnDiagonaleSup(Point(8,3)) && !this->possedePionAdverseEnDiagonaleSup(Point(8,4))){
                    listeCoupsPossibles.push_back(Position("c8")); // Case du grand roque
                }
            }


        }

    }
}


/*
* On vérifie que la position ou souhaite allez le Roi est dans aucune listeCoupsPossibles de 
* toutes les pièces adverses.
*/
bool Roi::posDansLCPAdverse(const string &position) const{
    for(Piece *p : getListePiece()){
        if(p->getCouleur() != this->getCouleur() && p->getNomString() != "Pion"){
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

    if(this->getCouleur() == "Blanc"){

        bool diagoSupGauche(false);
        bool diagoSupDroite(false);

        // Diagonale gauche supérieure ↖
        if(estCorrectPoint(p) && estCorrectPoint(p+Point(1,-1)) && existePieceSurPosition(convertPointToPosition(p+Point(1,-1)))){
            if(existePieceSurPosition(convertPointToPosition(p+Point(1,-1)))->getNomString() == "Pion" && existePieceSurPosition(convertPointToPosition(p+Point(1,-1)))->getCouleur() != this->getCouleur()){
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
            if(existePieceSurPosition(convertPointToPosition(p+Point(1,1)))->getNomString() == "Pion" && existePieceSurPosition(convertPointToPosition(p+Point(1,1)))->getCouleur() != this->getCouleur()){
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
    else if(this->getCouleur() == "Noir"){

        bool diagoInfGauche(false);
        bool diagoInfDroite(false);


        // Diagonale gauche inférieure ↙
        if(estCorrectPoint(p) && estCorrectPoint(p+Point(-1,-1)) && existePieceSurPosition(convertPointToPosition(p+Point(-1,-1)))){
            if(existePieceSurPosition(convertPointToPosition(p+Point(-1,-1)))->getNomString() == "Pion" && existePieceSurPosition(convertPointToPosition(p+Point(-1,-1)))->getCouleur() != this->getCouleur()){
                // Il existe une pièce et il s'agit d'un Pion adverse
                diagoInfGauche = true;
            }
            else{
                // Il existe une pièce et il ne s'agit pas d'un Pion adverse
                diagoInfGauche = false;
            }
        }
        else{
            // La position n'est pas correcte OU il n'existe pas de pièce sur cette position
            diagoInfGauche = false;
        }

        // Diagonale droite inférieure ↘
        if(estCorrectPoint(p) && estCorrectPoint(p+Point(-1,1)) && existePieceSurPosition(convertPointToPosition(p+Point(-1,1)))){
            if(existePieceSurPosition(convertPointToPosition(p+Point(-1,1)))->getNomString() == "Pion" && existePieceSurPosition(convertPointToPosition(p+Point(-1,1)))->getCouleur() != this->getCouleur()){
                // Il existe une pièce et il s'agit d'un Pion adverse
                diagoInfDroite = true;
            }
            else{
                // Il existe une pièce et il ne s'agit pas d'un Pion adverse
                diagoInfDroite = false;
            }
        }
        else{
            // La position n'est pas correcte OU il n'existe pas de pièce sur cette position
            diagoInfDroite = false;
        }

        return diagoInfGauche || diagoInfDroite;
    }
    else{
        cout << "Erreur : impossible déterminer si le roi possède un pion en diagonaleSup/diagonaleInf." << endl;
        return false;
    }

    
}

Roi::~Roi(){}


bool estEnEchecRoi(string Couleur){

    if(Couleur == "Blanc"){
        bool estEnEchec = false;

        for(Piece *p : getListePiece()){
            if(p->getNomString() == "Roi" && p->getCouleur() == "Blanc"){

                Position posRoiBlanc = p->getPosition();

                for(Piece *q : getListePiece()){
                    if(q->getCouleur() != "Blanc"){
                        for(Position pos : q->getListeCoupsPossibles()){
                            if(pos.getCoord() == posRoiBlanc.getCoord()){
                                estEnEchec = true;
                            }
                        }
                    }
                }
            }
        }

        return estEnEchec;
    }
    else if(Couleur == "Noir"){

        bool estEnEchec = false;

        for(Piece *p : getListePiece()){
            if(p->getNomString() == "Roi" && p->getCouleur() == "Noir"){

                Position posRoiBlanc = p->getPosition();

                for(Piece *q : getListePiece()){
                    if(q->getCouleur() != "Noir"){
                        for(Position pos : q->getListeCoupsPossibles()){
                            if(pos.getCoord() == posRoiBlanc.getCoord()){
                                estEnEchec = true;
                            }
                        }
                    }
                }
            }
        }

        return estEnEchec;
    }


    return 0; // Ça n'arrive jamais
}