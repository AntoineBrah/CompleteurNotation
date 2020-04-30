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

Pion::Pion(Couleur c, type::Nom n, string pos) : Piece(c,n,pos){}

void Pion::updateListeCoupsPossibles(){

    listeCoupsPossibles.clear(); // On vide la liste actuelle des coups possibles 

    if(this->getNomString() == "Pion" && this->getPositionString() != "NULL"){

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

        /****************/
        /* Pion : BLANC */
        /****************/

        if(this->getCouleur() == "Blanc"){
            // Tout pion blanc peut avancer 2 cases(ligne+2) devant lui s'il n'a jamais bougé (↑ vers le haut)
            // On vérifie que le Pion n'a jamais bougé
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'aucune Pièce n'est présent sur la case ligne+1
            // Puis on vérifie également qu'aucun pion n'est présent sur la case ligne+2
            if(!aBouge){        
                if(estCorrectPoint(positionPion+Point(2,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(2,0)))) && estCorrectPoint(positionPion+Point(1,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(1,0)))))
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(2,0)));
            }

            // Tout pion peut avancer 1 case (ligne+1) devant lui (↑ vers le haut)
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'aucune Pièce n'est présent sur la case ligne+1
            if(estCorrectPoint(positionPion+Point(1,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(1,0))))){
                listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,0)));
            }

            // Tout pion peut avancer en diagonale gauche (ligne+1,col-1) si il y a une pièce de couleur opposé (il le mange donc) (↖ diagonale supérieure gauche)
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'une Pièce est présente sur la case (col+1, ligne-1)
            // On vérifie que la Pièce est de couleur opposé
            if(estCorrectPoint(positionPion+Point(1,-1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,-1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,-1)))->getCouleur() != this->getCouleur())
                listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,-1)));

            // Tout pion peut avancer en diagonale droite (ligne+1,col+1) si il y a une pièce de couleur opposé (il le mange donc) (➚ diagonale supérieure droite)
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'une Pièce est présent sur la case (col+1, ligne+1)
            // On vérifie que la Pièce est de couleur opposé
            if(estCorrectPoint(positionPion+Point(1,1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(1,1)))->getCouleur() != this->getCouleur())
                listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,1)));


            // Implémentation de la prise en passant (↖ diagonale supérieure gauche)
            if(this->getPosition().getLigne() == "5" && estCorrectPoint(positionPion+Point(0,-1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1)))->getNomString() == "Pion" &&  existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1)))->getCouleur() == "Noir" && !existePieceSurPosition(convertPointToPosition(positionPion+Point(1,-1)))){
                Piece *p = existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1)));
                
                // Ici on vérifie que le pion noir est bien le dernier coup qui a été joué jusqu'à présent (car la prise en passant ne dure qu'1 tour...)
                if(getDernierCSP(p->getFirstCell()) == getDernierCSE()){
                
                    // Maintenant on vérifie que le pion noir a bien avancé de 2 cases d'un coup
                    if(abs((convertPositionToPoint(getDernierCSP(p->getFirstCell())->getPositionCell())-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getX()) == 2){
                        listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,-1)));
                    }
                }
            }

            // Implémentation de la prise en passant (↗ diagonale supérieure droite)
            if(this->getPosition().getLigne() == "5" && estCorrectPoint(positionPion+Point(0,1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1)))->getNomString() == "Pion" &&  existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1)))->getCouleur() == "Noir" && !existePieceSurPosition(convertPointToPosition(positionPion+Point(1,1)))){
                Piece *p = existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1)));
                
                // Ici on vérifie que le pion noir est bien le dernier coup qui a été joué jusqu'à présent (car la prise en passant ne dure qu'1 tour...)
                if(getDernierCSP(p->getFirstCell()) == getDernierCSE()){
                
                    // Maintenant on vérifie que le pion noir a bien avancé de 2 cases d'un coup
                    if(abs((convertPositionToPoint(getDernierCSP(p->getFirstCell())->getPositionCell())-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getX()) == 2){
                        listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(1,1)));
                    }
                }
            }

        }

        /*****************/
        /*  Pion : NOIR  */
        /*****************/

        if(this->getCouleur() == "Noir"){
            // Tout pion noir peut avancer 2 cases (ligne-2) devant lui s'il n'a jamais bougé (↓ vers le bas)
            // On vérifie que le Pion n'a jamais bougé
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'aucune Pièce n'est présent sur la case ligne-1
            // Puis on vérifie également qu'aucun pion n'est présent sur la case ligne-2
            if(!aBouge){        
                if(estCorrectPoint(positionPion+Point(-2,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(-2,0)))) && estCorrectPoint(positionPion+Point(-1,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,0)))))
                    listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(-2,0)));
            }

            // Tout pion peut avancer 1 case (ligne-1) devant lui (↓ vers le bas)
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'aucune Pièce n'est présent sur la case ligne-1

            if(estCorrectPoint(positionPion+Point(-1,0)) && (!existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,0)))))
                listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(-1,0)));

            // Tout pion peut avancer en diagonale gauche (ligne-1,col-1) si il y a une pièce de couleur opposé (il le mange donc) (↙ diagonale inférieure gauche)
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'une Pièce est présente sur la case (col+1, ligne-1)
            // On vérifie que la Pièce est de couleur opposé
            if(estCorrectPoint(positionPion+Point(-1,-1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,-1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,-1)))->getCouleur() != this->getCouleur())
                listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(-1,-1)));

            // Tout pion peut avancer en diagonale droite (ligne-1,col+1) si il y a une pièce de couleur opposé (il le mange donc)  (➘ diagonale inférieure droite)
            // On vérifie que la case existe bien (en gros qu'on sort pas du plateau)
            // On vérifie qu'une Pièce est présent sur la case (ligne-1, col+1)
            // On vérifie que la Pièce est de couleur opposé
            if(estCorrectPoint(positionPion+Point(-1,1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,1)))->getCouleur() != this->getCouleur())
                listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(-1,1)));


            // Implémentation de la prise en passant (↙ diagonale inférieure gauche)
            if(this->getPosition().getLigne() == "4" && estCorrectPoint(positionPion+Point(0,-1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1)))->getNomString() == "Pion" &&  existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1)))->getCouleur() == "Blanc" && !existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,-1)))){
                Piece *p = existePieceSurPosition(convertPointToPosition(positionPion+Point(0,-1)));

                // Ici on vérifie que le pion blanc est bien le dernier coup qui a été joué jusqu'à présent (car la prise en passant ne dure qu'1 tour...)
                if(getDernierCSP(p->getFirstCell()) == getDernierCSE()){
                
                    // Maintenant on vérifie que le pion blanc a bien avancé de 2 cases d'un coup
                    if(abs((convertPositionToPoint(getDernierCSP(p->getFirstCell())->getPositionCell())-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getX()) == 2){
                        listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(-1,-1)));
                    }
                }
            }

            // Implémentation de la prise en passant (↘ diagonale inférieure droite)
            if(this->getPosition().getLigne() == "4" && estCorrectPoint(positionPion+Point(0,1)) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1))) && existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1)))->getNomString() == "Pion" &&  existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1)))->getCouleur() == "Blanc" && !existePieceSurPosition(convertPointToPosition(positionPion+Point(-1,1)))){
                Piece *p = existePieceSurPosition(convertPointToPosition(positionPion+Point(0,1)));
            
                // Ici on vérifie que le pion blanc est bien le dernier coup qui a été joué jusqu'à présent (car la prise en passant ne dure qu'1 tour...)
                if(getDernierCSP(p->getFirstCell()) == getDernierCSE()){
                
                    // Maintenant on vérifie que le pion blanc a bien avancé de 2 cases d'un coup
                    if(abs((convertPositionToPoint(getDernierCSP(p->getFirstCell())->getPositionCell())-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getX()) == 2){
                        listeCoupsPossibles.push_back(convertPointToPosition(positionPion+Point(-1,1)));
                    }
                }
            }


        }
    }

    if(this->getPositionString() != "NULL" && (this->getNomString() == "Dame" || this->getNomString() == "Fou" || this->getNomString() == "Tour")){

        Position currentPosition(pos);
        Point positionPiece = convertPositionToPoint(currentPosition);

        /*
        * Il faudra toujours vérifier que la position de la pièce
        * est toujours dans l'échiquier. Pour se faire on utilise
        * la fonction 'estCorrectPoint(Point)'.
        */

        if(this->getNomString() == "Dame" || this->getNomString() == "Tour"){

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
        }


        if(this->getNomString() == "Dame" || this->getNomString() == "Fou"){

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



    if(this->getPositionString() != "NULL" && this->getNomString() == "Cavalier"){

        Position currentPosition(pos);
        Point positionPiece = convertPositionToPoint(currentPosition);

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

Pion::~Pion(){}