#include "TraitementCoups.h"

void traitementCoups(lectureFichier* f){

    vector<Cellule*> *instancesEchiquier = initialiserCellules();
    // On l'utilise seulement pour effacer en mémoire les nouvelles cellules créées
    vector<Cellule*> nouvellesCellules; // On l'utilise seulement pour effacer en mémoire

    lectureFichier *File = f;

    int nbCoup = 0;
    Cellule *k = NULL; // contient l'adresse de la cellule de CSE

    do{
        string deplacementBlanc = f->getCoupBlanc();
        string deplacementNoir = f->getCoupNoir();

        if(deplacementBlanc != ""){

            nbCoup++;


            if(File->getCoupBlanc().size() == 3){

                string typePiece;
                string deplacement = string{File->getCoupBlanc()[1]} + File->getCoupBlanc()[2];

                switch(File->getCoupBlanc()[0]){
                    case 'T':
                        typePiece = "Tour";
                        break;
                    case 'C':
                        typePiece = "Cavalier";
                        break;
                    case 'F':
                        typePiece = "Fou";
                        break;
                    case 'D':
                        typePiece = "Dame";
                        break;
                    case 'R':
                        typePiece = "Roi";
                        break;
                    default:
                        cout << "ERREUR : Impossible de déterminer de quelle pièce il s'agit (coup blanc)." << endl;
                        break;
                }

                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Blanc" && instancesEchiquier->at(i)->getPiece()->getNom() == typePiece){

                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){
                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacement){

                                Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));

                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                instancesEchiquier->at(i)->getPiece()->setPostion(deplacement); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                nouvellesCellules.push_back(c); 

                                dernierCSP->setCSP(c);

                                k = c;

                                dernierCSP->setCSE(k);
                            }
                        }
                    }
                }
            }
            else if(File->getCoupBlanc().size() == 2){
            // C'est donc forcément un pion blanc

                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Blanc" && instancesEchiquier->at(i)->getPiece()->getNom() == "Pion"){

                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){
                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacementBlanc){
                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles

                                Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));

                                instancesEchiquier->at(i)->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                nouvellesCellules.push_back(c); 

                                dernierCSP->setCSP(c);

                                k = c;

                                dernierCSP->setCSE(k);
                            }
                        }
                    }
                }
            }
        }



        if(deplacementNoir != ""){

            nbCoup++;

            if(File->getCoupNoir().size() == 3){

                string typePiece;
                string deplacement = string{File->getCoupNoir()[1]} + File->getCoupNoir()[2];

                switch(File->getCoupNoir()[0]){
                    case 'T':
                        typePiece = "Tour";
                        break;
                    case 'C':
                        typePiece = "Cavalier";
                        break;
                    case 'F':
                        typePiece = "Fou";
                        break;
                    case 'D':
                        typePiece = "Dame";
                        break;
                    case 'R':
                        typePiece = "Roi";
                        break;
                    default:
                        cout << "ERREUR : Impossible de déterminer de quelle pièce il s'agit (coup noir)." << endl;
                        break;
                }

                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Noir" && instancesEchiquier->at(i)->getPiece()->getNom() == typePiece){
                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){
                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacement){
                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles

                                Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));

                                instancesEchiquier->at(i)->getPiece()->setPostion(deplacement); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                nouvellesCellules.push_back(c); 

                                dernierCSP->setCSP(c);

                                k = c;

                                dernierCSP->setCSE(k);
                            }
                        }
                    }
                }
            }
            else if(File->getCoupNoir().size() == 2){
            // C'est donc forcément un pion noir

                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Noir" && instancesEchiquier->at(i)->getPiece()->getNom() == "Pion"){

                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){
                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacementNoir){
                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles

                                Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));

                                instancesEchiquier->at(i)->getPiece()->setPostion(deplacementNoir); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                nouvellesCellules.push_back(c); 

                                dernierCSP->setCSP(c);

                                k = c;

                                dernierCSP->setCSE(k);
                            }
                        }
                    }
                }
            }
        }
        



    }while(File->lireLigneSuivante());


    // On efface le contenu des vectors (mémoire dynamique)
    for(Cellule* cell : (*instancesEchiquier)){
        delete cell->getPiece(); // On efface la pièce contenu dans la cellule
        delete cell; // On efface la cellule
    }
    
    
    for(Cellule* cell : nouvellesCellules){
        delete cell;
    }
    
    instancesEchiquier->clear();
    nouvellesCellules.clear();
    

}
