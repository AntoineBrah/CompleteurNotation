#include "TraitementCoups.h"

void traitementCoups(lectureFichier* f){

    vector<Cellule*> *instancesEchiquier = initialiserCellules();

    lectureFichier *File = f;

    int nbCoup = 0;
    Cellule *k = NULL; // contient l'adresse de la cellule de CSE
    
    do{
        nbCoup++;

        string deplacementBlanc = f->getCoupBlanc();
        string deplacementNoir = f->getCoupNoir();

        if(deplacementBlanc != ""){

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

                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Blanc" && cell->getPiece()->getNomString() == typePiece){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacement){
                                if(nbCoup == 1){
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());

                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);

                                    k=c;
                                }
                                else{
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    
                                    
                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());

                                    dernierCSP->setCSP(c);
                                    k->setCSE(c);

                                    k=c;
                                }
                            }
                        }
                    }
                }
            }
            else if(File->getCoupBlanc().size() == 2){
            // C'est donc forcément un pion blanc
                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Blanc" && cell->getPiece()->getNomString() == "Pion"){
                        Cellule *dernierCSP = getDernierCSP(cell);
                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacementBlanc){
                                if(nbCoup == 1){
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());


                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);

                                    k=c;
                                }
                                else{
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    
                                    
                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());

                                    dernierCSP->setCSP(c);
                                    k->setCSE(c);

                                    k=c;
                                }
                            }
                        }
                    }
                }
            }
        }

        if(deplacementNoir != ""){
            
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
                
                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Noir" && cell->getPiece()->getNomString() == typePiece){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            
                            if(pos.getCoord() == deplacement){
                                
                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(cell->getPiece());

                                dernierCSP->setCSP(c);
                                k->setCSE(c);

                                k=c;
                            }
                        }
                    }
                }
            }
            else if(File->getCoupNoir().size() == 2){
            // C'est donc forcément un pion noir

                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Noir" && cell->getPiece()->getNomString() == "Pion"){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacementNoir){
                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                cell->getPiece()->setPostion(deplacementNoir); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                
                                
                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(cell->getPiece());

                                dernierCSP->setCSP(c);
                                k->setCSE(c);

                                k=c;
                            }
                        }
                    }
                }
            }
        }

    }while(File->lireLigneSuivante());

    // On ajoute les infos de chaque cellules dans notre fichier JSON
    for(Cellule* cell : (*getListeCellule())){
        //cout << cell->toString() << endl;
        ecritureFichier(cell->getJSON() + ",");
    }


    // On efface le contenu des vectors (mémoire dynamique)
    for(Cellule* cell : (*instancesEchiquier)){
        delete cell->getPiece(); // On efface la pièce contenu dans la cellule
        delete cell; // On efface la cellule
    }
    
    instancesEchiquier->clear();
}
