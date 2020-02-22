#include "TraitementCoups.h"

void traitementCoups(lectureFichier* f){

    vector<Cellule*> *instancesEchiquier = initialiserCellules();
    vector<Cellule*> nouvellesCellules;

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

                
                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Blanc" && instancesEchiquier->at(i)->getPiece()->getNom() == typePiece){

                        Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));

                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){

                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacement){
                                
                                // Cas de la premiere pièce bougé, forcément un Cavalier
                                if(nbCoup == 1){

                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    instancesEchiquier->at(i)->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                    nouvellesCellules.push_back(c);

                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);

                                    k=c;
                                }
                                else{
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    dernierCSP->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                    nouvellesCellules.push_back(c);

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

                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Blanc" && instancesEchiquier->at(i)->getPiece()->getNom() == "Pion"){

                        Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));

                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){

                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacementBlanc){

                                
                                // Cas de la premiere pièce bougé, forcément un Pion
                                if(nbCoup == 1){

                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    instancesEchiquier->at(i)->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                    nouvellesCellules.push_back(c);

                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);

                                    k=c;
                                }
                                else{
                                    
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    instancesEchiquier->at(i)->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    
                                    
                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                    nouvellesCellules.push_back(c);

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

                
                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Noir" && instancesEchiquier->at(i)->getPiece()->getNom() == typePiece){
                        
                        Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));

                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){

                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacement){
                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles

                                
                                instancesEchiquier->at(i)->getPiece()->setPostion(deplacement); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                nouvellesCellules.push_back(c);

                                // On met à jour CSP de notre cellule
                                dernierCSP->setCSP(c);

                                // On met à jour le "zig-zag" entre cellules
                                k->setCSE(c);

                            

                                k=c;
                            }
                        }
                    }
                }
            }
            else if(File->getCoupNoir().size() == 2){
            // C'est donc forcément un pion noir

                for(unsigned int i=0; i<instancesEchiquier->size(); i++){
                    if(instancesEchiquier->at(i)->getPiece()->getCouleur() == "Noir" && instancesEchiquier->at(i)->getPiece()->getNom() == "Pion"){
                        
                        Cellule *dernierCSP = getDernierCSP(instancesEchiquier->at(i));


                        for(unsigned int j=0; j<instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->size(); j++){

                            if(instancesEchiquier->at(i)->getPiece()->getListeCoupsPossibles()->at(j).getCoord() == deplacementNoir){
                                // On récupère la première pièce possèdant cette position dans sa liste des coups possibles

                                
                                instancesEchiquier->at(i)->getPiece()->setPostion(deplacementNoir); // on déplace la pièce
                                updateListeCoupsPossiblesAll(); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                cout << instancesEchiquier->at(i)->getPiece()->toString() << endl;
                                instancesEchiquier->at(i)->getPiece()->printListeCoupsPossibles();

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(instancesEchiquier->at(i)->getPiece());
                                nouvellesCellules.push_back(c);

                                // On met à jour CSP de notre cellule
                                dernierCSP->setCSP(c);

                                // On met à jour le "zig-zag" entre cellules
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
