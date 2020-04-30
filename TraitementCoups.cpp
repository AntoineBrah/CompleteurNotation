#include "TraitementCoups.h"

void seFaitMangerPiece(Piece* p){

    cout << endl << "[+] -> " << p->getNomString() << " " << p->getCouleur() << " en position : " << p->getPosition().getCoord() << " vient de se faire manger.\n" << endl;

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

bool traitementCoups(string path){

    analyseCoups(path); // on analyse la partie avant de corriger les erreurs

    lectureFichier gameFile(path);

    if(!gameFile.getEstCorrectementOuvert()){
        return false; // On sort immédiatement de traitementCoups car le fichier n'existe pas
    }

    cout << "[*] Début du traitement des coups...\n" << endl;
    
    vector<Cellule*> *instancesEchiquier = initialiserCellules();

    lectureFichier *File = &gameFile;

    int nbCoup = 0;
    Cellule *k = NULL; // contient l'adresse de la cellule de CSE
    
    do{
        //cout << "Coup n°" << nbCoup << endl;
        nbCoup++;
        
        string deplacementBlanc = File->getCoupBlanc();
        string deplacementNoir = File->getCoupNoir();

        vector<string> descBlanc = File->getDescriptionCb();
        vector<string> descNoir = File->getDescriptionCn();


        if(!descBlanc.empty()){
            //separator();
            //cout << "Piece : " << descBlanc[0] << "\nColonne : " << descBlanc[1] << "\nLigne : " << descBlanc[2] << "\nDeplacement : " << descBlanc[3] << "\nPromotion : " << descBlanc[4] << "\nEchec : " << descBlanc[5] << endl << endl;
            //separator();
        }

        if(!descNoir.empty()){
            //separator();
            //cout << "\nPiece : " << descNoir[0] << "\nColonne : " << descNoir[1] << "\nLigne : " << descNoir[2] << "\nDeplacement : " << descNoir[3] << "\nPromotion : " << descNoir[4] << "\nEchec : " << descNoir[5] << endl << endl;
            //separator();
        }

        
        if(!descBlanc.empty() && descBlanc[0]=="Null"){
          Cellule* cVierge = new Cellule();
          k->setCSE(cVierge);
          cVierge->setCPE(k);
          k = cVierge;
        }
        

        else if(deplacementBlanc != ""){

            string typePiece = descBlanc[0];
            string deplacement = descBlanc[3];

            verificationDeplacementPiece(k, deplacementBlanc, "Blanc", descBlanc, nbCoup, File);
            
        }

        // Si le tout premier coup joué (coup blanc) est faux, les listes ne peuvent pas être générées correctement
        if(nbCoup == 1 && k == NULL){
            cout << "[!] : ARRÊT DU PROGRAMME : Le premier coup de la partie (joueur blanc) étant faux, il est impossible générer la structure de chaînage correctement." << endl;
            return false;
        }

        
        if(!descNoir.empty() && descNoir[0]=="Null"){
          Cellule* cVierge = new Cellule();
          k->setCSE(cVierge);
          cVierge->setCPE(k);
          k = cVierge;
        }
        

        else if(deplacementNoir != ""){
            
            string typePiece = descNoir[0];
            string deplacement = descNoir[3];

            verificationDeplacementPiece(k, deplacementNoir, "Noir", descNoir, nbCoup, File);
        }
    }while(File->lireLigneSuivante());

    

    // On ajoute les infos de chaque cellules dans notre fichier JSON
    for(Cellule* cell : getListeCellule()){
        ecritureFichier("Interface/cellules.json",cell->getJSON() + ",");
        cout << cell->toString() << endl;
    }

    // On rajoute le ']' à la fin du fichier
    correctionSyntaxe("Interface/cellules.json");

    
    coupOublie(k);
    affichagePartieJuste(k);
    

    // On efface le contenu des vectors (mémoire dynamique)
    for(Cellule* cell : (*instancesEchiquier)){
        delete cell->getPiece(); // On efface la pièce contenu dans la cellule
        delete cell; // On efface la cellule
    }
    
    instancesEchiquier->clear();

    return true;
}


/******************************/
/******************************/
/******************************/


bool analyseCoups(string path){

    cout << "[*] Début de l'analyse des coups...\n" << endl;

    lectureFichier gameFile(path);

    if(!gameFile.getEstCorrectementOuvert()){
        return false; // On sort immédiatement de traitementCoups car le fichier n'existe pas
    }
    
    vector<Cellule*> *instancesEchiquier = initialiserCellules();

    lectureFichier *File = &gameFile;

    int nbCoup = 0;
    Cellule *k = NULL; // contient l'adresse de la cellule de CSE
    
    do{
        //cout << "Coup n°" << nbCoup << endl;
        nbCoup++;
        
        string deplacementBlanc = File->getCoupBlanc();
        string deplacementNoir = File->getCoupNoir();

        vector<string> descBlanc = File->getDescriptionCb();
        vector<string> descNoir = File->getDescriptionCn();

        if(!descBlanc.empty()){
            //separator();
            //cout << "Piece : " << descBlanc[0] << "\nColonne : " << descBlanc[1] << "\nLigne : " << descBlanc[2] << "\nDeplacement : " << descBlanc[3] << "\nPromotion : " << descBlanc[4] << "\nEchec : " << descBlanc[5] << endl << endl;
            //separator();
        }

        if(!descNoir.empty()){
            //separator();
            //cout << "\nPiece : " << descNoir[0] << "\nColonne : " << descNoir[1] << "\nLigne : " << descNoir[2] << "\nDeplacement : " << descNoir[3] << "\nPromotion : " << descNoir[4] << "\nEchec : " << descNoir[5] << endl << endl;
            //separator();
        }

        if(deplacementBlanc != ""){

            string typePiece = descBlanc[0];
            string deplacement = descBlanc[3];

            if(typePiece != "Pion"){

                for(Piece* p : getListePiece()){
                    if(p->getCouleur() == "Blanc" && p->getNomString() == typePiece && ((descBlanc[1] == "" || p->getPosition().getColonne() == descBlanc[1]) && (descBlanc[2] == "" || p->getPosition().getLigne() == descBlanc[2])) && appartientLCP(p, deplacement)){
                        
                        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());
                                                
                        if(nbCoup == 1){
                            // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                            p->setPostion(deplacement); // on déplace la pièce

                            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                            Cellule *c = new Cellule(p);
                            c->copieListeCoupsPossibles(dernierCSP);

                            dernierCSP->setCSP(c);
                            dernierCSP->setCSE(c);
                            c->setCPP(dernierCSP);
                            c->setCPE(dernierCSP);

                            k=c;

                            updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                        }
                        else{
                            Position pos = Position(deplacement); // On stock la position initiale de la pièce

                            Piece *p2 = NULL; // On récupère la pièce qui se situe sur le déplacement
                            
                            if(existePieceSurPosition(deplacement)){
                                p2 = existePieceSurPosition(deplacement);
                                seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                            }

                            p->setPostion(deplacement); // on déplace la pièce
                            updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                            
                            if(estEnEchecRoi("Blanc")){
                                // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                // et on ne créé pas de nouvelle cellule


                                p->setPostion(pos.getCoord());

                                if(p2 != NULL){
                                    annulationSeFaitMangerPiece(p2, deplacement);
                                }

                                updateListeCoupsPossiblesAll(false);
                                cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                            }
                            else{
                                // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                                p->setPostion(deplacement); // on déplace la pièce

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(p);
                                c->copieListeCoupsPossibles(dernierCSP);

                                dernierCSP->setCSP(c);
                                k->setCSE(c);
                                c->setCPP(dernierCSP);
                                c->setCPE(k);

                                k=c;

                                // On déplace juste la Tour (on a déplacé le Roi auparavant)
                                /* Cas ou le Roi Blanc Roque */
                                if(p->getNomString() == "Roi" && deplacement == "g1" && (Point(1,7)-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getY() == 2){ // Petit Roque
                                    
                                    Piece *t = existePieceSurPosition("h1"); // La Tour en h1 qu'on bouge (elle existe forcément car si le roi possède g1 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                                    t->setPostion("f1"); // On déplace la tour en f1

                                    // On s'occupe des cellules de la Tour
                                    Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP
                                    Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                                    tmp->setCSP(deplacementTour);
                                    deplacementTour->setCPP(tmp);
                                    deplacementTour->copieListeCoupsPossibles(tmp);

                                }
                                else if(p->getNomString() == "Roi" && deplacement == "c1" && (convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())-Point(1,3)).getY() == 2){ // Grand Roque
                                    
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
            else if(typePiece == "Pion"){ // C'est donc forcément un pion blanc
            
                for(Piece *p : getListePiece()){
                    if(p->getCouleur() == "Blanc" && p->getNomString() == "Pion" && (descBlanc[1] == "" || p->getPosition().getColonne() == descBlanc[1]) && appartientLCP(p, deplacement)){

                        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());

                        if(nbCoup == 1){
                            // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                            p->setPostion(deplacement); // on déplace la pièce

                            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                            Cellule *c = new Cellule(p);
                            c->copieListeCoupsPossibles(dernierCSP);

                            dernierCSP->setCSP(c);
                            dernierCSP->setCSE(c);
                            c->setCPP(dernierCSP);
                            c->setCPE(dernierCSP);
                        
                            k=c;
                            updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                        }
                        else{
                            
                            Position pos = Position(deplacement); // On stock la position initiale de la pièce
                            
                            Piece *p2(NULL); // On récupère la pièce qui se situe sur le déplacement

                            bool prendEnPassant = false;
                            
                            
                            if(existePieceSurPosition(deplacement)){
                                p2 = existePieceSurPosition(deplacement);
                                seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                            }
                            else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)))->getCouleur() == "Noir" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)))->getNomString() == "Pion"){
                                // Cas ou on prend en passant
                                p2 = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)));
                                cout << "Prise en passant : " << endl;
                                seFaitMangerPiece(p2);
                                prendEnPassant = true;
                            }


                            p->setPostion(deplacement); // on déplace la pièce
                            updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                            
                            if(estEnEchecRoi("Blanc")){
                                // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                // et on ne créé pas de nouvelle cellule

                                p->setPostion(pos.getCoord());

                                if(p2 != NULL){
                                    if(!prendEnPassant)
                                        annulationSeFaitMangerPiece(p2, deplacement);
                                    else
                                        annulationSeFaitMangerPiece(p2, convertPointToPosition(convertPositionToPoint(deplacement)-Point(1,0)));
                                }
                                
                                updateListeCoupsPossiblesAll(false);
                                cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                            }
                            else{
                                // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                // Dans cette situation tout se déroule comme quand le Roi n'est pas en
                                
                                p->setPostion(deplacement); // on déplace la pièce

                                // S'il y a une promotion
                                if(p->getPosition().getLigne() == "8" && descBlanc[4] != ""){
                                    cout << "--> Promotion du pion blanc en " << descBlanc[3] << endl << endl; 
                                    p->setNom(descBlanc[4]);
                                } 

                                // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                Cellule *c = new Cellule(p);
                                c->copieListeCoupsPossibles(dernierCSP);
                                
                                dernierCSP->setCSP(c);
                                k->setCSE(c);
                                c->setCPP(dernierCSP);
                                c->setCPE(k);
                                
                                k=c;
                                updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces    
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
                
                for(Piece* p : getListePiece()){

                    if(p->getCouleur() == "Noir" && p->getNomString() == typePiece && ((descNoir[1] == "" || p->getPosition().getColonne() == descNoir[1]) && (descNoir[2] == "" || p->getPosition().getLigne() == descNoir[2])) && appartientLCP(p, deplacement)){

                        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());
                        
                        Position pos = Position(deplacement); // On stock la position initiale de la pièce

                        Piece *p2(NULL); // On récupère la pièce qui se situe sur le déplacement

                        if(existePieceSurPosition(deplacement)){
                            p2 = existePieceSurPosition(deplacement);
                            seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                        }
                        
                        p->setPostion(deplacement); // on déplace la pièce
                        updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces

                        if(estEnEchecRoi("Noir")){
                            // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                            // et on ne créé pas de nouvelle cellule

                            p->setPostion(pos.getCoord());

                            if(p2 != NULL){
                                annulationSeFaitMangerPiece(p2, deplacement);
                            }

                            updateListeCoupsPossiblesAll(false);
                            cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                        }
                        else{
                            // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                            // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                            p->setPostion(deplacement); // on déplace la pièce
                            
                            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                            Cellule *c = new Cellule(p);
                            c->copieListeCoupsPossibles(dernierCSP);

                            dernierCSP->setCSP(c);
                            k->setCSE(c);
                            c->setCPP(dernierCSP);
                            c->setCPE(k);

                            k=c;

                            // On déplace juste la Tour (on a déplacé le Roi auparavant)
                            /* Cas ou le Roi Noir Roque */
                            if(p->getNomString() == "Roi" && deplacement == "g8" && (Point(8,7)-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getY() == 2){ // Petit Roque

                                Piece *t = existePieceSurPosition("h8"); // La Tour en h8 qu'on bouge (elle existe forcément car si le roi possède g8 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                                t->setPostion("f8"); // On déplace la tour en f8

                                // On s'occupe des cellules de la Tour
                                Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP
                                Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                                tmp->setCSP(deplacementTour);
                                deplacementTour->setCPP(tmp);
                                deplacementTour->copieListeCoupsPossibles(tmp);

                            }
                            else if(p->getNomString() == "Roi" && deplacement == "c8" && (convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())-Point(8,3)).getY() == 2){ // Grand Roque

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
            else if(typePiece == "Pion"){ // C'est donc forcément un pion noir

                for(Piece* p : getListePiece()){
                    if(p->getCouleur() == "Noir" && p->getNomString() == "Pion" && (descNoir[1] == "" || p->getPosition().getColonne() == descNoir[1]) && appartientLCP(p, deplacement)){

                        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());

                        Position pos = Position(deplacement); // On stock la position initiale de la pièce
                        
                        Piece *p2(NULL); // On récupère la pièce qui se situe sur le déplacement

                        bool prendEnPassant = false;
                            
                        if(existePieceSurPosition(deplacement)){
                            p2 = existePieceSurPosition(deplacement);
                            seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                        }
                        else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)))->getCouleur() == "Blanc" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)))->getNomString() == "Pion"){
                            // Cas ou on prend en passant
                            p2 = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)));
                            cout << "Prise en passant : " << endl;
                            seFaitMangerPiece(p2);
                            prendEnPassant = true;
                        }

                        p->setPostion(deplacement); // on déplace la pièce
                        updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                        
                        if(estEnEchecRoi("Noir")){
                            // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                            // et on ne créé pas de nouvelle cellule

                            p->setPostion(pos.getCoord());

                            if(p2 != NULL){
                                if(!prendEnPassant)
                                    annulationSeFaitMangerPiece(p2, deplacement);
                                else
                                    annulationSeFaitMangerPiece(p2, convertPointToPosition(convertPositionToPoint(deplacement)+Point(1,0)));
                            }

                            updateListeCoupsPossiblesAll(false);
                            cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                        }
                        else{
                            // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                            // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                            p->setPostion(deplacement); // on déplace la pièce


                            // S'il y a une promotion
                            if(p->getPosition().getLigne() == "1" && descNoir[4] != ""){
                                cout << "--> Promotion du pion noir en " << descNoir[3] << endl;
                                p->setNom(descNoir[4]);
                            } 
                            
                            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                            Cellule *c = new Cellule(p);
                            c->copieListeCoupsPossibles(dernierCSP);

                            dernierCSP->setCSP(c);
                            k->setCSE(c);
                            c->setCPP(dernierCSP);
                            c->setCPE(k);

                            k=c;
                            updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièce
                        }
                    }
                }
            }
        }
    }while(File->lireLigneSuivante());
    

    // On ajoute les infos de chaque cellules dans notre fichier JSON
    for(Cellule* cell : getListeCellule()){
        ecritureFichier("Interface/cellulesBis.json", cell->getJSON() + ",");
    }

    // On rajoute le ']' à la fin du fichier
    correctionSyntaxe("Interface/cellulesBis.json"); 

    // On efface le contenu des vectors (mémoire dynamique)
    for(Cellule* cell : (*instancesEchiquier)){
        delete cell->getPiece(); // On efface la pièce contenu dans la cellule
        delete cell; // On efface la cellule
    }

    getListePiece().clear();
    getListeCellule().clear();
    instancesEchiquier->clear();

    return true;
}
