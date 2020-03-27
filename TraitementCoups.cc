#include "TraitementCoups.h"

void seFaitMangerPiece(Piece* p){

    cout << "[+] -> " << p->getNomString() << " " << p->getCouleur() << " en position : " << p->getPosition().getCoord() << " vient de se faire manger.\n" << endl;

    p->setPostion("NULL"); // On sort la pièce du plateau

    // On créér la cellule qui représente la mort de la pièce (Position : NULL, CSP : NULL, CSE : NULL)
    Cellule *mortPiece = new Cellule(p);
    mortPiece->setCSP(NULL);
    mortPiece->setCSE(NULL);

    Cellule *tmp = getDernierCSP(p->getFirstCell());

    mortPiece->setCPP(tmp);

    tmp->setCSP(mortPiece); // On chaine l'avant dernière cellule de la pièce avec la dernière (la dernière représentant la mort de la pièce)

    updateListeCoupsPossiblesAll(false); // On met à jour la liste des coups possibles de toutes les pièces et on vide celle de la pièce qui vient de mourir par la même occasion
}

void annulationSeFaitMangerPiece(Piece* p, Position pos){

    p->setPostion(pos.getCoord()); // On remet la pièce à sa position
    updateListeCoupsPossiblesAll(false); // On met à jour la liste des coups possibles de tout le monde

    cout << "[-] -> " << p->getNomString() << " " << p->getCouleur() << " en position : " << pos.getCoord() << " annulation du fait qu'il se soit fait manger.\n" << endl;

    Cellule *c1 = p->getFirstCell();
    Cellule *tmp = c1;
    
    while(c1->getCSP()){
        tmp = c1;
        c1 = c1->getCSP(); // c1 devient la dernière cellule des Cellules de CSP de la pièce
    }
    
    tmp->setCSP(NULL); // On enlève le lien entre l'avant dernière et la dernière cellule des CSP de la pièce
    delete c1; // On supprime la dernière cellule 
}

bool traitementCoups(lectureFichier* f){
    
    vector<Cellule*> *instancesEchiquier = initialiserCellules();

    lectureFichier *File = f;

    int nbCoup = 0;
    Cellule *k = NULL; // contient l'adresse de la cellule de CSE
    
    do{
        nbCoup++;
        
        string deplacementBlanc = f->getCoupBlanc();
        string deplacementNoir = f->getCoupNoir();

        vector<string> descBlanc = f->getDescriptionCb();
        vector<string> descNoir = f->getDescriptionCn();


        if(!descBlanc.empty()){
            cout << "\nPiece : " << descBlanc[0] << "\nColonne : " << descBlanc[1] << "\nLigne : " << descBlanc[2] << "\nDeplacement : " << descBlanc[3] << "\nPromotion : " << descBlanc[4] << "\nEchec : " << descBlanc[5] << endl << endl;
        }

        if(!descNoir.empty()){
            cout << "\nPiece : " << descNoir[0] << "\nColonne : " << descNoir[1] << "\nLigne : " << descNoir[2] << "\nDeplacement : " << descNoir[3] << "\nPromotion : " << descNoir[4] << "\nEchec : " << descNoir[5] << endl << endl;
        }

        if(deplacementBlanc != ""){

            string typePiece = descBlanc[0];
            string deplacement = descBlanc[3];

            if(descBlanc[0] != "Pion"){

                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Blanc" && cell->getPiece()->getNomString() == typePiece && ((descBlanc[1] == "" || cell->getPiece()->getPosition().getColonne() == descBlanc[1]) && (descBlanc[2] == "" || cell->getPiece()->getPosition().getLigne() == descBlanc[2]))){

                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            
                            /**********************************************************************************************************************************************/
                            
                            if(pos.getCoord() == deplacement){
                                
                                if(nbCoup == 1){
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);
                                    c->setCPP(dernierCSP);

                                    k=c;

                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                }
                                else{
                                    Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce

                                    Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement
                                    
                                    if(existePieceSurPosition(deplacement)){
                                        p = existePieceSurPosition(deplacement);
                                        seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                    }

                                    

                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                                    
                                    if(estEnEchecRoiBlanc()){
                                        // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                        // et on ne créé pas de nouvelle cellule

                                        cell->getPiece()->setPostion(pos.getCoord());

                                        if(p != NULL){
                                            annulationSeFaitMangerPiece(p, deplacement);
                                        }

                                        updateListeCoupsPossiblesAll(false);
                                        cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                    }
                                    else{
                                        // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                        // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec
                                
                                        cell->getPiece()->setPostion(deplacement); // on déplace la pièce

                                        // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                        Cellule *c = new Cellule(cell->getPiece());
                                        c->copieListeCoupsPossibles(dernierCSP);

                                        dernierCSP->setCSP(c);
                                        k->setCSE(c);
                                        c->setCPP(dernierCSP);

                                        k=c;

                                        
                                        /* Cas ou le Roi Blanc Roque */
                                        if(cell->getPiece()->getNomString() == "Roi" && deplacement == "g1" && (Point(1,7)-convertPositionToPoint(getDernierCSP(cell)->getCPP()->getPositionCell())).getY() == 2){ // Petit Roque
                                            
                                            Piece *t = existePieceSurPosition("h1"); // La Tour en h1 qu'on bouge (elle existe forcément car si le roi possède g1 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                                            t->setPostion("f1"); // On déplace la tour en f1

                                            // On s'occupe des cellules de la Tour
                                            Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP
                                            Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                                            tmp->setCSP(deplacementTour);
                                            deplacementTour->setCPP(tmp);
                                            deplacementTour->copieListeCoupsPossibles(tmp);

                                        }
                                        else if(cell->getPiece()->getNomString() == "Roi" && deplacement == "c1" && (convertPositionToPoint(getDernierCSP(cell)->getCPP()->getPositionCell())-Point(1,3)).getY() == 2){ // Grand Roque
                                            
                                            Piece *t = existePieceSurPosition("a1"); // La Tour en a1 qu'on bouge (elle existe forcément car si le roi possède c1 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                                            t->setPostion("d1"); // On déplace la tour en d1

                                            // On s'occupe des cellules de la Tour
                                            Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP 
                                            Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                                            tmp->setCSP(deplacementTour);
                                            deplacementTour->setCPP(tmp);
                                            deplacementTour->copieListeCoupsPossibles(tmp);

                                        }
                                        
                                        updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(descBlanc[0] == "Pion"){
            
            // C'est donc forcément un pion blanc
                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Blanc" && cell->getPiece()->getNomString() == "Pion" && (descBlanc[1] == "" || cell->getPiece()->getPosition().getColonne() == descBlanc[1])){

                        Cellule *dernierCSP = getDernierCSP(cell);
                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacement){

                                if(nbCoup == 1){
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);
                                    c->setCPP(dernierCSP);
                                
                                    k=c;
                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                }
                                else{
                                    
                                    Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce
                                    
                                    Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement

                                    bool prendEnPassant = false;
                                    
                                    if(existePieceSurPosition(deplacement)){
                                        p = existePieceSurPosition(deplacement);
                                        seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                    }
                                    else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)))->getCouleur() == "Noir" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)))->getNomString() == "Pion"){
                                        // Cas ou on prend en passant
                                        p = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)));
                                        cout << "Prise en passant : " << endl;
                                        seFaitMangerPiece(p);
                                        prendEnPassant = true;
                                    }

                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    
                                    if(estEnEchecRoiBlanc()){
                                        // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                        // et on ne créé pas de nouvelle cellule

                                        cell->getPiece()->setPostion(pos.getCoord());

                                        if(p != NULL){
                                            if(!prendEnPassant)
                                                annulationSeFaitMangerPiece(p, deplacement);
                                            else
                                                annulationSeFaitMangerPiece(p, convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)));
                                        }
                                        
                                        updateListeCoupsPossiblesAll(false);
                                        cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                    }
                                    else{
                                        // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                        // Dans cette situation tout se déroule comme quand le Roi n'est pas en 
                                        
                                        cell->getPiece()->setPostion(deplacement); // on déplace la pièce


                                        // S'il y a une promotion
                                        if(cell->getPiece()->getPosition().getLigne() == "8" && descBlanc[4] != ""){
                                            cout << "--> Promotion du pion blanc en " << descBlanc[3] << endl << endl; 
                                            cell->getPiece()->setNom(descBlanc[4]);
                                        } 

                                        // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                        Cellule *c = new Cellule(cell->getPiece());
                                        c->copieListeCoupsPossibles(dernierCSP);
                                        
                                        dernierCSP->setCSP(c);
                                        k->setCSE(c);
                                        c->setCPP(dernierCSP);
                                        
                                        k=c;
                                        updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Si le tout premier coup joué (coup blanc) est faux, les listes ne peuvent pas être générées correctement
        if(nbCoup == 1 && k == NULL){
            cout << "[!] : ARRÊT DU PROGRAMME : Le premier coup de la partie (joueur blanc) étant faux, il est impossible générer la structure de chaînage correctement." << endl;
            return false;
        }

        if(deplacementNoir != ""){
            
            string typePiece = descNoir[0];
            string deplacement = descNoir[3];

            if(typePiece != "Pion"){
                
                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Noir" && cell->getPiece()->getNomString() == typePiece && ((descNoir[1] == "" || cell->getPiece()->getPosition().getColonne() == descNoir[1]) && (descNoir[2] == "" || cell->getPiece()->getPosition().getLigne() == descNoir[2]))){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            
                            if(pos.getCoord() == deplacement){
                                
                                Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce

                                Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement
                                    
                                if(existePieceSurPosition(deplacement)){
                                    p = existePieceSurPosition(deplacement);
                                    seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                }
                                

                                cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                
                                if(estEnEchecRoiNoir()){
                                    // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                    // et on ne créé pas de nouvelle cellule

                                    cell->getPiece()->setPostion(pos.getCoord());

                                    if(p != NULL){
                                        annulationSeFaitMangerPiece(p, deplacement);
                                    }

                                    updateListeCoupsPossiblesAll(false);
                                    cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                }
                                else{
                                    // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                    // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    
                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    k->setCSE(c);
                                    c->setCPP(dernierCSP);

                                    k=c;

                                    /* Cas ou le Roi Noir Roque */
                                    if(cell->getPiece()->getNomString() == "Roi" && deplacement == "g8" && (Point(8,7)-convertPositionToPoint(getDernierCSP(cell)->getCPP()->getPositionCell())).getY() == 2){ // Petit Roque

                                        Piece *t = existePieceSurPosition("h8"); // La Tour en h8 qu'on bouge (elle existe forcément car si le roi possède g8 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                                        t->setPostion("f8"); // On déplace la tour en f8

                                        // On s'occupe des cellules de la Tour
                                        Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP
                                        Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                                        tmp->setCSP(deplacementTour);
                                        deplacementTour->setCPP(tmp);
                                        deplacementTour->copieListeCoupsPossibles(tmp);

                                    }
                                    else if(cell->getPiece()->getNomString() == "Roi" && deplacement == "c8" && (convertPositionToPoint(getDernierCSP(cell)->getCPP()->getPositionCell())-Point(8,3)).getY() == 2){ // Grand Roque

                                        Piece *t = existePieceSurPosition("a8"); // La Tour en a8 qu'on bouge (elle existe forcément car si le roi possède g1 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                                        t->setPostion("d8"); // On déplace la tour en d8

                                        // On s'occupe des cellules de la Tour
                                        Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP 
                                        Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                                        tmp->setCSP(deplacementTour);
                                        deplacementTour->setCPP(tmp);
                                        deplacementTour->copieListeCoupsPossibles(tmp);

                                    }

                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                }
                            }
                        }
                    }
                }
            }
            else if(typePiece == "Pion"){
            // C'est donc forcément un pion noir
                
                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Noir" && cell->getPiece()->getNomString() == "Pion" && (descNoir[1] == "" || cell->getPiece()->getPosition().getColonne() == descNoir[1])){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacement){
                                Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce
                                
                                Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement

                                bool prendEnPassant = false;
                                    
                                if(existePieceSurPosition(deplacement)){
                                    p = existePieceSurPosition(deplacement);
                                    seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                }
                                else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)))->getCouleur() == "Blanc" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)))->getNomString() == "Pion"){
                                    // Cas ou on prend en passant
                                    p = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)));
                                    cout << "Prise en passant : " << endl;
                                    seFaitMangerPiece(p);
                                    prendEnPassant = true;
                                }

                                cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                
                                if(estEnEchecRoiNoir()){
                                    // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                    // et on ne créé pas de nouvelle cellule

                                    cell->getPiece()->setPostion(pos.getCoord());

                                    if(p != NULL){
                                        if(!prendEnPassant)
                                                annulationSeFaitMangerPiece(p, deplacement);
                                        else
                                            annulationSeFaitMangerPiece(p, convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)));
                                    }

                                    updateListeCoupsPossiblesAll(false);
                                    cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                }
                                else{
                                    // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                    // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce


                                    // S'il y a une promotion
                                    if(cell->getPiece()->getPosition().getLigne() == "1" && descNoir[4] != ""){
                                        cout << "--> Promotion du pion noir en " << descNoir[3] << endl << endl;
                                        cell->getPiece()->setNom(descNoir[4]);
                                    } 
                                    
                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    k->setCSE(c);
                                    c->setCPP(dernierCSP);

                                    k=c;
                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièce
                                }
                            }
                        }
                    }
                }
            }
        }
    }while(File->lireLigneSuivante());

    // On ajoute les infos de chaque cellules dans notre fichier JSON
    for(Cellule* cell : (*getListeCellule())){
        ecritureFichier(cell->getJSON() + ",");
    }

    // On efface le contenu des vectors (mémoire dynamique)
    for(Cellule* cell : (*instancesEchiquier)){
        delete cell->getPiece(); // On efface la pièce contenu dans la cellule
        delete cell; // On efface la cellule
    }
    
    instancesEchiquier->clear();

    return true;
}
